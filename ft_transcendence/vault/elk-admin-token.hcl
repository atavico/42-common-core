path "secret/elk/kibana_service_token" {
  capabilities = [ "create", "read", "list", "update", "delete" ]
}

path "secret/elk/logstash_system_token" {
  capabilities = [ "create", "read", "list", "update", "delete" ]
}

path "secret/elk/elastic_token" {
  capabilities = [ "create", "read", "list", "update", "delete" ]
}

path "secret/*" {
  capabilities = [ "list" ]
}