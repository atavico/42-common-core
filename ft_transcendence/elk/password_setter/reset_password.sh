#!/bin/sh

chown -R 1000:1000 /usr/share/psw_res/elk-vault-shared/
echo "wait" > /usr/share/psw_res/elk-vault-shared/ls_system_completed.txt
echo "none" > /usr/share/psw_res/elk-vault-shared/elk_token.txt

vault_elk_token=$(cat /usr/share/psw_res/elk-vault-shared/elk_token.txt)
while true; do
	if [ "$vault_elk_token" != "none" ]; then
		break
	else
		sleep 5
		vault_elk_token=$(cat /usr/share/psw_res/elk-vault-shared/elk_token.txt)
	fi
done

max_attempts=10
delay_seconds=10
attempt=1

while [ $attempt -le $max_attempts ]; do
   response=$(curl -vik -H "X-Vault-Token: $vault_elk_token" https://vault:8200/v1/cubbyhole/elastic_token)
   echo "$response"
   if echo "$response" | grep -q "HTTP/2 200"; then
        echo "Request successful!"
        break
	fi
    ((attempt++))
    sleep $delay_seconds
done

el_token=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

response=$(curl -vik -H "X-Vault-Token: $vault_elk_token" https://vault:8200/v1/cubbyhole/logstash_system_token)

new_logstash_token=$(echo "$response" | awk -F '"' '{print $18}' | tr -d '[:space:]')

while true; do
	response=$(curl -vik -X POST "https://elasticsearch:9200/_security/user/elastic/_password?pretty" -u "elastic:$ELASTIC_PASSWORD" -H 'Content-Type: application/json' -d '
	{
		"password": "'"$el_token"'"
	}
	')
	if echo "$response" | grep -q "200 OK"; then
        echo "Request successful!"
        break
	fi
	echo "zzzzzz"
    sleep 10
done

curl -vik -X POST "https://elasticsearch:9200/_security/user/logstash_system/_password?pretty" -u "elastic:$el_token" -H 'Content-Type: application/json' -d'
{
  "password" : "'"$new_logstash_token"'"
}
'

echo "continue" > /usr/share/psw_res/elk-vault-shared/ls_system_completed.txt
sleep 13
rm /usr/share/psw_res/elk-vault-shared/ls_system_completed.txt

echo "kibana is ready"

while true; do
    response=$(curl -vik -X POST https://kibana:5601/api/saved_objects/_import -u "elastic:$el_token" -H "kbn-xsrf: true" --form file=@/usr/share/elasticsearch/config/dashboard.ndjson)
    
    if echo "$response" | grep -q "200 OK"; then
        echo "Request successful!"
        break
	fi
	echo "zzzzzz"
    sleep 5
done

curl -vik -X PUT "https://elasticsearch:9200/_ilm/policy/my_policy?pretty" -u "elastic:$el_token" -H 'Content-Type: application/json' -d'
{
  "policy": {
    "_meta": {
      "description": "used for nginx log",
      "project": {
        "name": "myProject",
        "department": "myDepartment"
      }
    },
    "phases": {
      "warm": {
        "min_age": "10d",
        "actions": {
          "forcemerge": {
            "max_num_segments": 1
          }
        }
      },
      "delete": {
        "min_age": "30d",
        "actions": {
          "delete": {}
        }
      }
    }
  }
}
'

curl -vik -X PUT "https://elasticsearch:9200/_index_template/apache_template?pretty" -u "elastic:$el_token" -H 'Content-Type: application/json' -d'
{
  "index_patterns": ["apache-*"],                 
  "template": {
    "settings": {
      "number_of_shards": 1,
      "number_of_replicas": 1,
      "index.lifecycle.name": "my_policy",      
      "index.lifecycle.rollover_alias": "timeseries"    
    }
  }
}
'




echo "__________pasword resetter exiting...__________"