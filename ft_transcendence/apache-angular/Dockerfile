FROM node:alpine3.17 as build-stage
WORKDIR /app
COPY angular-app/package*.json /app/
RUN npm install
COPY angular-app /app/
ARG IP_ADDR
ENV IP_ADDR=$IP_ADDR
RUN sed -i 's/localhost/'"${IP_ADDR}"'/g' src/environments/environment.ts
#RUN CI=true npm test
RUN npm run build
# Stage 1, based on ubuntu, to have only the compiled app, ready for production with apache

# Running Modsecurity in a Docker container;
FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
# Run system update/upgrade
RUN apt update -y && apt upgrade -y

# Install Required Build Tools and Dependencies
RUN apt install -y g++ flex bison curl apache2-dev \
	doxygen libyajl-dev ssdeep liblua5.2-dev \
	libgeoip-dev libtool dh-autoreconf \
	libcurl4-gnutls-dev libxml2 libpcre++-dev \
	libxml2-dev git wget tar apache2

# Download LibModsecurity Source Code
RUN wget https://github.com/SpiderLabs/ModSecurity/releases/download/v3.0.4/modsecurity-v3.0.4.tar.gz

# Extract the ModSecurity source code.
RUN tar xzf modsecurity-v3.0.4.tar.gz && rm -rf modsecurity-v3.0.4.tar.gz

# Compile and Install LibModsecurity
RUN cd modsecurity-v3.0.4 && \
	./build.sh && ./configure && \
	make && make install

# Install ModSecurity-Apache Connector
RUN cd ~ && git clone https://github.com/SpiderLabs/ModSecurity-apache

RUN cd ~/ModSecurity-apache && \
	./autogen.sh && \
	./configure --with-libmodsecurity=/usr/local/modsecurity/ && \
	make && \
	make install

# Load the Apache ModSecurity Connector Module
RUN echo "LoadModule security3_module /usr/lib/apache2/modules/mod_security3.so" >> /etc/apache2/apache2.conf

# Configure ModSecurity
RUN mkdir /etc/apache2/modsecurity.d && \
	cp modsecurity-v3.0.4/modsecurity.conf-recommended /etc/apache2/modsecurity.d/modsecurity.conf && \
	cp modsecurity-v3.0.4/unicode.mapping /etc/apache2/modsecurity.d/ && \
	sed -i 's/SecRuleEngine DetectionOnly/SecRuleEngine On/' /etc/apache2/modsecurity.d/modsecurity.conf
ADD modsec/modsec_rules.conf /etc/apache2/modsecurity.d/

# Install OWASP ModSecurity Core Rule Set (CRS) on Ubuntu
RUN git clone https://github.com/SpiderLabs/owasp-modsecurity-crs.git /etc/apache2/modsecurity.d/owasp-crs && \
	cp /etc/apache2/modsecurity.d/owasp-crs/crs-setup.conf.example /etc/apache2/modsecurity.d/owasp-crs/crs-setup.conf
# Activate ModSecurity
RUN mv /etc/apache2/sites-available/000-default.conf /etc/apache2/sites-available/000-default.conf.old
ADD conf/000-default.conf /etc/apache2/sites-available/

#Copy of builded react
COPY --from=build-stage /app/dist /var/www/html/transcendence
COPY angular-app/src/app/pagenotfound/404.html /var/www/html/transcendence/frontend/error_pages/404.html

#Enable https
RUN a2enmod ssl 
COPY tls-certificates/localhost.crt /etc/apache2/ssl/cert.crt
COPY tls-certificates/localhost.key /etc/apache2/ssl/cert-key.key

EXPOSE 80
EXPOSE 443
#CMD apachectl -D FOREGROUND
ENTRYPOINT ["apachectl", "-D", "FOREGROUND"]
