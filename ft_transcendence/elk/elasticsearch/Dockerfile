FROM elasticsearch:8.12.0
COPY elasticsearch.yml /usr/share/elasticsearch/config/elasticsearch.yml
COPY tls-certificates/ /usr/share/elasticsearch/config
COPY generate_credentials.sh /usr/share/elasticsearch/config/generate_credentials
CMD /usr/share/elasticsearch/config/generate_credentials