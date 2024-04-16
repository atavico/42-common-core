/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_handle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:08:53 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 16:08:10 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	player_handle(t_game *game, int y, int x)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->img->xpm_image_pl, x * 64, y * 64);
}

void	wall_handle(t_game *game, int y, int x)
{
	if (game->img->collectible_count == 0)
	{
		if (game->img->frame < 40)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->img->xpm_image_erb1, x * 64, y * 64);
		else if (game->img->frame < 80)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->img->xpm_image_erb2, x * 64, y * 64);
		else if (game->img->frame < 120)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->img->xpm_image_erb3, x * 64, y * 64);
		else if (game->img->frame < 160)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
				game->img->xpm_image_erb4, x * 64, y * 64);
	}
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
						game->img->xpm_image_wall, x * 64, y * 64);
}

void	collect_handle(t_game *game, int y, int x)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->img->xpm_image_coll, x * 64, y * 64);
}

void	exit_handle(t_game *game, int y, int x)
{
	if (game->img->collectible_count == 0)
	{
		if (game->img->frame < 40)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->img->xpm_image_blackhole1, x * 64, y * 64);
		else if (game->img->frame < 80)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->img->xpm_image_blackhole2, x * 64, y * 64);
		else if (game->img->frame < 120)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->img->xpm_image_blackhole3, x * 64, y * 64);
		else if (game->img->frame < 160)
			mlx_put_image_to_window(game->mlx, game->mlx_win, \
			game->img->xpm_image_blackhole4, x * 64, y * 64);
	}
	else
		mlx_put_image_to_window(game->mlx, game->mlx_win, \
		game->img->xpm_image_exit, x * 64, y * 64);
}

void	draw(t_game *game, int i, int j)
{
	if (game->matrix[i][j] == 'C')
		collect_handle(game, i, j);
	else if (game->matrix[i][j] == '1')
		wall_handle(game, i, j);
	else if (game->matrix[i][j] == 'P')
		player_handle(game, i, j);
	else if (game->matrix[i][j] == 'E')
		exit_handle(game, i, j);
}	
