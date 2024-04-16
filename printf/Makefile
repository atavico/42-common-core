# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 14:58:09 by atarsi            #+#    #+#              #
#    Updated: 2022/02/10 19:02:06 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRCS =	ft_printchar.c ft_printf.c ft_printhexalower.c ft_printhexaupper.c ft_printint.c ft_printpercent.c ft_printptr.c \
		ft_printstring.c ft_printunsint.c ft_putchar.c ft_putnbr_hexalower.c ft_putnbr_hexaupper.c ft_putnbr.c ft_putstr.c ft_strlen.c 
OBJS = $(SRCS:.c=.o)
HDRS = ft_printf.h
FLAGS = -Wall -Wextra -Werror

$(NAME):
		gcc -c $(FLAGS) -I $(HDRS) $(SRCS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

all:	$(NAME)

clean:
		rm -f $(OBJS)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

.PHONY:	all clean fclean re