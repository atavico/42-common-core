# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 14:44:15 by atarsi            #+#    #+#              #
#    Updated: 2022/04/29 16:33:44 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
SRCS = so_long.c check_validity.c free_all.c command_handle.c img_to_win.c \
		init_all.c matrix.c movement.c
HDRS = libft.h
FLAGS = -Wall -Wextra -Werror -g
LIBFT = libft/libft.a
LIBFT_DIR = libft/
LINKS = -l mlx -framework OpenGL -framework AppKit

$(NAME):
		make -C $(LIBFT_DIR)
		gcc $(SRCS) $(LINKS) $(FLAGS) -I $(HDRS) $(LIBFT) -o $(NAME)

all:	$(NAME)

clean:
		make fclean -C ./libft

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean bonus re