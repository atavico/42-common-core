# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/13 18:06:51 by atarsi            #+#    #+#              #
#    Updated: 2022/06/13 19:42:24 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
NAME_BONUS = checker
SRCS = main.c split_char.c utility.c swap.c pre_alg.c rotate.c push.c re_rotate.c ft_algoritmo.c check.c ft_atoi2.c free_all.c ft_countmoves.c ft_lis.c
SRCS_BONUS = checker.c split_char.c utility.c swap.c pre_alg.c rotate.c push.c re_rotate.c ft_algoritmo.c check.c ft_atoi2.c free_all.c ft_countmoves.c
FLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a

$(NAME):
		make -C libft
		gcc $(FLAGS) $(SRCS) -o $(NAME) $(LIBFT)

bonus:
		make -C libft
		gcc $(FLAGS) $(SRCS_BONUS) -o $(NAME_BONUS) $(LIBFT)

all: $(NAME)

clean:
		make fclean -C libft
		rm -rf $(NAME) $(NAME_BONUS)

fclean: clean

re: fclean all bonus