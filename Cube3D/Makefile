ARCH = $(shell uname -m)
NAME= cub3d
CC = gcc
SRC = main.c read_file.c utility.c init.c check.c check_extra.c texture.c draw_utils.c draw.c movements.c 
OBJS = $(SRC:.c=.o)
FLAG = -g -Wall -Werror -Wextra
LIB = ./libft/libft.a
MLX	= ./libmlx.dylib
MLXA = ./libmlx.dylib

%.o: %.c
			$(CC) ${FLAG} -g -c $< -o $@ 

all: $(NAME)

$(NAME):$(OBJS)
	@(test -f $(MLX)  && echo "\033[32mlibft already built\033[0m") || (make -C ./minilibx && mv minilibx/libmlx.dylib .)
	$(CC) $(FLAG) -o $(NAME) $(LIB) $(OBJS) $(MLX)
	@(echo "\033[32mCube_3D>> Compiled\033[0m")
a:
	@(test -f $(MLX)  && echo "\033[32mMLX already built\033[0m") || (make -C ./amlx && mv amlx/libmlx.dylib .)
	gcc $(FLAG) $(SRC) $(MLXA) $(LIB) -o $(NAME)
	@(echo "\033[32mCube_3D>> Compiled\033[0m")

$(LIB):
	@$(MAKE) -C ./libft


clean:
	rm -rf $(OBJS) 

fclean: clean
		rm -f $(NAME) libmlx.dylib


re: fclean all