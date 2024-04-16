#!/bin/sh

set -e

# Files created by Elasticsearch should always be group writable too
umask 0002

# Allow user specify custom CMD, maybe bin/elasticsearch itself
# for example to directly specify `-E` style parameters for elasticsearch on k8s
# or simply to run /bin/bash to check the image
if [[ "$1" == "eswrapper" || $(basename "$1") == "elasticsearch" ]]; then
  # Rewrite CMD args to remove the explicit command,
  # so that we are backwards compatible with the docs
  # from the previous Elasticsearch versions < 6
  # and configuration option:
  # https://www.elastic.co/guide/en/elasticsearch/reference/5.6/docker.html#_d_override_the_image_8217_s_default_ulink_url_https_docs_docker_com_engine_reference_run_cmd_default_command_or_options_cmd_ulink
  # Without this, user could specify `elasticsearch -E x.y=z` but
  # `bin/elasticsearch -E x.y=z` would not work. In any case,
  # we want to continue through this script, and not exec early.
  set -- "${@:2}"
else
  # Run whatever command the user wanted
  exec "$@"
fi

# Allow environment variables to be set by creating a file with the
# contents, and setting an environment variable with the suffix _FILE to
# point to it. This can be used to provide secrets to a container, without
# the values being specified explicitly when running the container.
#
# This is also sourced in elasticsearch-env, and is only needed here
# as well because we use ELASTIC_PASSWORD below. Sourcing this script
# is idempotent.
source /usr/share/elasticsearch/bin/elasticsearch-env-from-file

if [[ -f bin/elasticsearch-users ]]; then
  # Check for the ELASTIC_PASSWORD environment variable to set the
  # bootstrap password for Security.
  #
  # This is only required for the first node in a cluster with Security
  # enabled, but we have no way of knowing which node we are yet. We'll just
  # honor the variable if it's present.
  if [[ -n "$ELASTIC_PASSWORD" ]]; then
    [[ -f /usr/share/elasticsearch/config/elasticsearch.keystore ]] || (elasticsearch-keystore create)
    if ! (elasticsearch-keystore has-passwd --silent) ; then
      # keystore is unencrypted
      if ! (elasticsearch-keystore list | grep -q '^bootstrap.password$'); then
        (echo "$ELASTIC_PASSWORD" | elasticsearch-keystore add -x 'bootstrap.password')
      fi
    else
      # keystore requires password
      if ! (echo "$KEYSTORE_PASSWORD" \
          | elasticsearch-keystore list | grep -q '^bootstrap.password$') ; then
        COMMANDS="$(printf "%s\n%s" "$KEYSTORE_PASSWORD" "$ELASTIC_PASSWORD")"
        (echo "$COMMANDS" | elasticsearch-keystore add -x 'bootstrap.password')
      fi
    fi
  fi
fi

if [[ -n "$ES_LOG_STYLE" ]]; then
  case "$ES_LOG_STYLE" in
    console)
      # This is the default. Nothing to do.
      ;;
    file)
      # Overwrite the default config with the stack config. Do this as a
      # copy, not a move, in case the container is restarted.
      cp -f /usr/share/elasticsearch/config/log4j2.file.properties /usr/share/elasticsearch/config/log4j2.properties
      ;;
    *)
      echo "ERROR: ES_LOG_STYLE set to [$ES_LOG_STYLE]. Expected [console] or [file]" >&2
      exit 1 ;;
  esac
fi

if [[ -n "$ENROLLMENT_TOKEN" ]]; then
  POSITIONAL_PARAMETERS="--enrollment-token $ENROLLMENT_TOKEN"
else
  POSITIONAL_PARAMETERS=""
fi

content=$(cat /usr/share/elasticsearch/elk-vault-shared/ls_system_completed.txt)
while true; do
	if [ "$content" = "wait" ]; then
		break
	else
		echo ".....................................elasticsearch waiting....................................."
		sleep 2
		content=$(cat /usr/share/elasticsearch/elk-vault-shared/ls_system_completed.txt)
	fi
done

echo "wait" > /usr/share/elasticsearch/elk-vault-shared/st_completed.txt
output=$(bin/elasticsearch-service-tokens create elastic/kibana token1)
ks_token=$(echo "$output" | awk '{print $NF}')
echo "generated elastic/kibana service token $ks_token"

max_attempts=10
delay_seconds=5
attempt=1

while [ $attempt -le $max_attempts ]; do
    curl -vik https://vault:8200 && break
    ((attempt++))
    sleep $delay_seconds
done
sleep $delay_seconds

vault_token=$(cat /usr/share/elasticsearch/elk-vault-shared/elk_token.txt)
curl -vik \
    --header "X-Vault-Token: $vault_token" \
    --request POST \
    --data '{"kibana_service_token": "'"$ks_token"'"}' \
    https://vault:8200/v1/cubbyhole/kibana_service_token

elk_admin_token=$(cat /usr/share/elasticsearch/elk-vault-shared/elk_admin_token.txt)
curl -vik \
    --header "X-Vault-Token: $elk_admin_token" \
    --request POST \
    --data '{"kibana_service_token": "'"$ks_token"'"}' \
    https://vault:8200/v1/secret/elk/kibana_service_token

echo "continue" > /usr/share/elasticsearch/elk-vault-shared/st_completed.txt
sleep 10
rm /usr/share/elasticsearch/elk-vault-shared/st_completed.txt
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!elastisearch starting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

# Signal forwarding and child reaping is handled by `tini`, which is the
# actual entrypoint of the container
exec /usr/share/elasticsearch/bin/elasticsearch "$@" $POSITIONAL_PARAMETERS <<<"$KEYSTORE_PASSWORD"