# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 18:04:37 by atarsi            #+#    #+#              #
#    Updated: 2023/01/19 18:29:22 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  = Fixed
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