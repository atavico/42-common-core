FROM alpine:3.13

RUN apk update && apk upgrade && apk add --no-cache \
    mariadb \
    mariadb-client

COPY tools/mariadb.sh /tmp/mariadb.sh

ENTRYPOINT [ "sh", "/tmp/mariadb.sh" ]