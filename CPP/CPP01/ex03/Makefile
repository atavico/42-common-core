# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/08 22:29:52 by atarsi            #+#    #+#              #
#    Updated: 2023/01/25 16:13:16 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = weaponnn
CC = c++
FLAG = -std=c++98 -Wall -Werror -Wextra
RM = rm -f

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
HEADER = Weapon.hpp HumanA.hpp HumanB.hpp

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