FROM kibana:8.12.0
COPY kibana.yml /usr/share/kibana/config
COPY tls-certificates/ /usr/share/kibana/config

COPY get_credentials.sh /usr/share/kibana/config/get_credentials

ENTRYPOINT ["/usr/share/kibana/config/get_credentials"]