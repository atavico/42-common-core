/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 17:24:46 by atarsi            #+#    #+#             */
/*   Updated: 2022/04/30 16:18:59 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	val_height_width(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->matrix[0][x] != '1' \
			|| game->matrix[game->height - 1][x] != '1')
				return (0);
			if (game->matrix[y][0] != '1' \
			|| game->matrix[y][game->width - 1] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

void	counter(t_game *game, int i, int j)
{
	if (game->matrix[i][j] == 'P')
	{
		game->img->player_x = j;
		game->img->player_y = i;
		game->c_player++;
	}
	else if (game->matrix[i][j] == 'C')
		game->img->collectible_count++;
	else if (game->matrix[i][j] == 'E')
		game->c_exit++;
}

int	val_player_coll(t_game *game)
{
	int	i;
	int	j;

	game->c_player = 0;
	game->c_exit = 0;
	game->img->collectible_count = 0;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			counter(game, i, j);
			j++;
		}
		i++;
	}
	if (game->c_player != 1 || game->img->collectible_count < 1 \
	|| game->c_exit < 1)
		return (0);
	return (1);
}

int	check_validity(t_game *game)
{
	if (val_height_width(game) == 0 || val_player_coll(game) == 0)
		return (0);
	return (1);
}
