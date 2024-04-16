# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                              ()             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/02 21:37:50 by atarsi            #+#    #+#              #
#    Updated: 2023/01/03 23:50:38 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = BraiiiiiiinnnzzzZ
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
