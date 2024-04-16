import logging
if not __name__ == "__main__":
	from django.conf import settings

logging.addLevelName( logging.DEBUG, "[\033[36mDEBUG \033[1;0m]:\033[36m")
logging.addLevelName( logging.INFO, "[\033[32mINFO  \033[1;0m]:\033[32m")
logging.addLevelName( logging.WARNING, "[\033[33mWARN  \033[1;0m]:\033[33m")
logging.addLevelName( logging.ERROR, "[\033[31mERROR \033[1;0m]:\033[31m")

log = logging.Logger("default", logging.DEBUG)

filler = "\033[33mDjango     	|\033[1;0m"
if not __name__ == "__main__" and settings.APP == "Daphne":
	filler = "\033[36mDaphne     	|\033[1;0m"

formatter = logging.Formatter(f"\r{filler} " + "%(levelname)s %(message)s\033[1;0m")

ch = logging.StreamHandler()
ch.setLevel(log.level)
ch.setFormatter(formatter)

log.addHandler(ch)


printe = log.error
printw = log.warning
printd = log.debug
printi = log.info

if __name__ == "__main__":
	log.info("hey there! That's a test line")
	log.error("hey there! That's a test line")
	log.debug("hey there! That's a test line")
	log.warning("hey there! That's a test line")
