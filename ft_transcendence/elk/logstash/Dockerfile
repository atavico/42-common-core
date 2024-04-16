FROM logstash:8.12.0
COPY logstash.conf /usr/share/logstash
COPY tls-certificates/ /usr/share/logstash/config
COPY logstash.yml /usr/share/logstash/config
COPY get_ls_system_psw.sh /usr/share/logstash/config/get_psw

ENTRYPOINT ["/usr/share/logstash/config/get_psw"]
#CMD logstash -f /usr/share/logstash/logstash.conf --log.level debug && chmod +r /usr/share/logstash/shared-volume/*