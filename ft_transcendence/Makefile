NAME=transcendence

$(NAME):
	docker compose up --build
# 	docker image prune -f
# 	docker system prune -f

stop:
	docker compose down

clean:
	docker compose down --volumes

free:
	docker rmi -f $(shell docker images -a -q)

prune: stop rm-apache-log
	docker system prune -a --volumes

rm-apache-log:
	> apache-angular/logs/access.log && > apache-angular/logs/error.log && > apache-angular/logs/other_vhosts_access.log
