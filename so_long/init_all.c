/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 15:28:50 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 16:32:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>

void	init_base(t_game *game)
{
	int	x;
	int	y;

	game->img->xpm_image_pl = mlx_xpm_file_to_image
		(game->mlx, "./sprite/shaman.xpm", &x, &y);
	game->img->xpm_image_wall = mlx_xpm_file_to_image
		(game->mlx, "./sprite/wall.xpm", &x, &y);
	game->img->xpm_image_exit = mlx_xpm_file_to_image
		(game->mlx, "./sprite/blackhole.xpm", &x, &y);
	game->img->xpm_image_coll = mlx_xpm_file_to_image
		(game->mlx, "./sprite/mush.xpm", &x, &y);
}

void	init_anim(t_game *game)
{
	int	x;
	int	y;

		game->img->xpm_image_erb1 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/erb1.xpm", &x, &y);
	game->img->xpm_image_erb2 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/erb2.xpm", &x, &y);
	game->img->xpm_image_erb3 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/erb3.xpm", &x, &y);
	game->img->xpm_image_erb4 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/erb4.xpm", &x, &y);
	game->img->xpm_image_blackhole1 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/blackhole1.xpm", &x, &y);
	game->img->xpm_image_blackhole2 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/blackhole2.xpm", &x, &y);
	game->img->xpm_image_blackhole3 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/blackhole3.xpm", &x, &y);
	game->img->xpm_image_blackhole4 = mlx_xpm_file_to_image
		(game->mlx, "./sprite/blackhole4.xpm", &x, &y);
}

void	init_images(t_game *game)
{
	game->img->xpm_image_pl = NULL;
	game->img->xpm_image_wall = NULL;
	game->img->xpm_image_exit = NULL;
	game->img->xpm_image_coll = NULL;
	game->img->xpm_image_erb1 = NULL;
	game->img->xpm_image_erb2 = NULL;
	game->img->xpm_image_erb3 = NULL;
	game->img->xpm_image_erb4 = NULL;
	game->img->xpm_image_blackhole1 = NULL;
	game->img->xpm_image_blackhole2 = NULL;
	game->img->xpm_image_blackhole3 = NULL;
	game->img->xpm_image_blackhole4 = NULL;
	game->img->frame = 0;
	init_base(game);
	init_anim(game);
}
