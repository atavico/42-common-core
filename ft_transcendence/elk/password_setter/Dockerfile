FROM alpine:3.19
COPY reset_password.sh /usr/share/elasticsearch/config/generate_credentials
COPY Kibana_apache_ModSecurity.ndjson /usr/share/elasticsearch/config/dashboard.ndjson
RUN apk --no-cache add curl
CMD /usr/share/elasticsearch/config/generate_credentials