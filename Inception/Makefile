all: prune re

down:
	@ sudo docker-compose -f srcs/docker-compose.yml down

clean: down
	@ sudo rm -rf /home/atarsi/data/wordpress/
	@ sudo rm -rf /home/atarsi/data/mariadb/

prune: clean
	@ sudo docker system prune -a -f

re:
	mkdir -p /home/atarsi/data/wordpress
	mkdir -p /home/atarsi/data/mariadb
	@ sudo docker-compose -f srcs/docker-compose.yml up --build

linux:
	@ sudo echo "127.0.0.1 atarsi.42.fr" >> /etc/hosts

.PHONY: all re down clean
