# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/20 17:35:07 by atarsi            #+#    #+#              #
#    Updated: 2022/06/20 17:35:07 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = *.c
FLG = -Wall -Werror -Wextra # -fsanitizer=address -g3

all: $(NAME)

$(NAME):
			gcc $(FLAG) -pthread $(SRC)  -o $(NAME)
clean:
			rm -f $(NAME)
fclean: clean

norm:
	@norminette

re:			fclean all
