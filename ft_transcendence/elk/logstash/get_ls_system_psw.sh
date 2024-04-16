#!/bin/sh

sleep 20
content=$(cat /usr/share/logstash/elk-vault-shared/ls_system_completed.txt)
while true; do
	if [ "$content" = "continue" ]; then
		break
	else
		echo ".....................................logstash waiting....................................."
		sleep 10
		content=$(cat /usr/share/logstash/elk-vault-shared/ls_system_completed.txt)
	fi
done


vault_elk_token=$(cat /usr/share/logstash/elk-vault-shared/elk_token.txt)

response=$(curl -vik -H "X-Vault-Token: $vault_elk_token" https://vault:8200/v1/cubbyhole/logstash_system_token)
logstash_system_token=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

response=$(curl -vik -H "X-Vault-Token: $vault_elk_token" https://vault:8200/v1/cubbyhole/elastic_token)
elastic_token=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

echo "GMEOLIIIII $logstash_system_token"
echo "GMEOLIPT2 $elastic_token"
export LS_TOKEN=$logstash_system_token
export EL_TOKEN=$elastic_token
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!logstash starting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

logstash -f /usr/share/logstash/logstash.conf --pipeline.unsafe_shutdown && chmod +r /usr/share/logstash/shared-volume/*