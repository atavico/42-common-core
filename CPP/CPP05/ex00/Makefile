# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alessandrotarsi <alessandrotarsi@studen    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 15:19:06 by atarsi            #+#    #+#              #
#    Updated: 2023/02/19 19:35:16 by alessandrot      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = bureaucrat
CC = c++
FLAG = -std=c++98 -Wall -Werror -Wextra
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