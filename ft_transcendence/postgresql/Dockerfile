FROM postgres:15-alpine

COPY tls-certificates/ /var/ssl/
RUN chown postgres /var/ssl/*
RUN chgrp postgres /var/ssl/*
RUN chmod 600 /var/ssl/*

COPY setup-postgres /docker-entrypoint-initdb.d/setup.sh

#RUN chmod +x /docker-entrypoint-initdb.d/setup.sh