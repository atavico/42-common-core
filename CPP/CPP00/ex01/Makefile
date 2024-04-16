# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/29 15:29:00 by atarsi            #+#    #+#              #
#    Updated: 2023/01/24 20:24:12 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###PROGRAM### 

NAME = phonebook

###COMPILER###

CC = c++
FLAGS = -std=c++98 -Wall -Werror -Wextra
RM = rm -f

###SOURCES###

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
HEADER = Contact.hpp PhoneBook.hpp

###RULES###

all: $(NAME)

%.o: %.cpp
		$(CC) $(FLAGS) -c $<

$(NAME) : $(OBJ)
		$(CC) $(FLAG) $(OBJ) -o $@

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all
