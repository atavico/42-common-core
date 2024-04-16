# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/17 12:00:33 by atarsi            #+#    #+#              #
#    Updated: 2023/01/25 16:40:41 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Harl
CC = c++
FLAG = -std=c++98 -Wall -Wextra -Werror
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

%.o : %.cpp
		$(CC) $(FLAG) -c $<
$(NAME) : $(OBJ)
		$(CC) $(FLAG) $(OBJ) -o $@

clean: 
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all