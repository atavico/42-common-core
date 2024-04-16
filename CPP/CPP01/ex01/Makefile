# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 12:08:01 by atarsi            #+#    #+#              #
#    Updated: 2023/01/31 17:47:01 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Moarbrainz
CC = c++
FLAG = -std=c++98 -Wall -Werror -Wextra
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
HEADER = Zombie.hpp

all: $(NAME)

%.o::%.cpp
		$(CC) $(FLAG) -c $<
$(NAME) : $(OBJ)
		$(CC) $(FLAG) $(OBJ) -o $@

clean:
		$(RM) $(OBJ)
fclean: clean
		$(RM) $(NAME)

re: fclean all
