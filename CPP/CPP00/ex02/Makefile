# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/31 14:09:10 by atarsi            #+#    #+#              #
#    Updated: 2023/01/24 20:48:31 by atarsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = the_job_of_your_dream
CC = c++
FLAGS = -std=c++98 -Wall -Werror -Wextra
RM = rm -rf

SRC = $(wildcard *.cpp)
OBJ = $(SRC:.cpp=.o)
HEADER = Account.hpp

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