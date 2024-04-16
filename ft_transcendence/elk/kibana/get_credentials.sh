#!/bin/sh

content=$(cat /usr/share/kibana/elk-vault-shared/st_completed.txt)
while true; do
	if [ "$content" = "continue" ]; then
		break
	else
		echo ".....................................kibana waiting....................................."
		sleep 7
		content=$(cat /usr/share/kibana/elk-vault-shared/st_completed.txt)
	fi
done

elk_token=$(cat /usr/share/kibana/elk-vault-shared/elk_token.txt)
response=$(curl -vik -H "X-Vault-Token: $elk_token" https://vault:8200/v1/cubbyhole/kibana_encryptionkey)
en_key=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

export KIBANA_ENCRYPTIONKEY=$en_key

response=$(curl -vik -H "X-Vault-Token: $elk_token" https://vault:8200/v1/cubbyhole/kibana_service_token)
service_account_token=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

export SA_TOKEN=$service_account_token
echo "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!kibana starting!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"

kibana