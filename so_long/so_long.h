/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:43:58 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 17:10:45 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_img
{
	void	*xpm_image_pl;
	void	*xpm_image_coll;
	void	*xpm_image_exit;
	void	*xpm_image_wall;
	void	*xpm_image_erb1;
	void	*xpm_image_erb2;
	void	*xpm_image_erb3;
	void	*xpm_image_erb4;
	void	*xpm_image_blackhole1;
	void	*xpm_image_blackhole2;
	void	*xpm_image_blackhole3;
	void	*xpm_image_blackhole4;
	int		player_x;
	int		player_y;
	int		collectible_count;
	int		move;
	int		frame;
}				t_img;

typedef struct s_game
{
	void	*mlx;
	void	*mlx_win;
	char	**matrix;
	int		width;
	int		height;
	int		x_size;
	int		y_size;
	int		c_player;
	int		c_exit;
	t_img	*img;
}				t_game;

int		read_map(t_game *game, char *filename);
void	alloc_matrix(t_game *game, char *filename);
int		check_validity(t_game *game);
void	img_to_win(t_game *game);
void	init_collect_count(t_game *game, int i, int j);
int		place_map(t_game *game);
void	img_init(t_img *img);
void	game_init(t_game *game);
void	init_images(t_game *game);
void	player_handle(t_game *game, int i, int j);
void	wall_handle(t_game *game, int i, int j);
void	collect_handle(t_game *game, int i, int j);
void	exit_handle(t_game *game, int i, int j);
void	draw(t_game *game, int i, int j);
int		ft_exit(char *str);
void	free_all(t_game *game);
void	move_up(t_game *game);
void	move_down(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);

#endif
