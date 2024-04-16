# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/18 17:36:03 by atarsi            #+#    #+#              #
#    Updated: 2023/02/01 15:57:55 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =harlFilter
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