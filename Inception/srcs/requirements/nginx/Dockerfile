FROM	alpine:3.13

#install all the program
RUN apk update && apk upgrade && apk add --no-cache \
       nginx \
       openssl

# nginx SSL
RUN mkdir /etc/nginx/ssl
RUN openssl req -newkey rsa:4096 -x509 -sha256 -days 365 -nodes \
       -out /etc/nginx/ssl/atarsi.pem \
       -keyout /etc/nginx/ssl/atarsi.key \
       -subj "/C=FR/ST=Rome/L=Rome/O=42 School/OU=atarsi/CN=atarsi/"

COPY ./conf/nginx.conf /etc/nginx/conf.d

# nginx config
RUN mkdir -p /run/nginx
COPY conf/nginx.conf /etc/nginx/conf.d/default.conf

# Start nginx
ENTRYPOINT ["nginx", "-g", "daemon off;"]

