/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 18:11:25 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 16:36:18 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_up(t_game *game)
{
	int	y;
	int	x;
	int	col;

	y = game->img->player_y;
	x = game->img->player_x;
	col = game->img->collectible_count;
	if (game->matrix[y - 1][x] != '1' &&
		(game->matrix[y - 1][x] != 'E' || col == 0))
	{
		if (game->matrix[y - 1][x] == 'E')
		{
			free_all(game);
			ft_exit("You win!\n");
		}
		if (game->matrix[y - 1][x] == 'C')
			game->img->collectible_count--;
		game->matrix[y][x] = '0';
		game->matrix[y - 1][x] = 'P';
		game->img->move++;
		game->img->player_y -= 1;
	}
}

void	move_down(t_game *game)
{
	int	y;
	int	x;
	int	col;

	y = game->img->player_y;
	x = game->img->player_x;
	col = game->img->collectible_count;
	if (game->matrix[y + 1][x] != '1' &&
		(game->matrix[y + 1][x] != 'E' || col == 0))
	{
		if (game->matrix[y + 1][x] == 'E')
		{
			free_all(game);
			ft_exit("You win!\n");
		}
		if (game->matrix[y + 1][x] == 'C')
			game->img->collectible_count--;
		game->matrix[y][x] = '0';
		game->matrix[y + 1][x] = 'P';
		game->img->move++;
		game->img->player_y += 1;
	}
}

void	move_right(t_game *game)
{
	int	y;
	int	x;
	int	col;

	y = game->img->player_y;
	x = game->img->player_x;
	col = game->img->collectible_count;
	if (game->matrix[y][x + 1] != '1' &&
		(game->matrix[y][x + 1] != 'E' || col == 0))
	{
		if (game->matrix[y][x + 1] == 'E')
		{
			free_all(game);
			ft_exit("You win!\n");
		}
		if (game->matrix[y][x + 1] == 'C')
			game->img->collectible_count--;
		game->matrix[y][x] = '0';
		game->matrix[y][x + 1] = 'P';
		game->img->move++;
		game->img->player_x += 1;
	}
}

void	move_left(t_game *game)
{
	int	y;
	int	x;
	int	col;

	y = game->img->player_y;
	x = game->img->player_x;
	col = game->img->collectible_count;
	if (game->matrix[y][x - 1] != '1' &&
		(game->matrix[y][x - 1] != 'E' || col == 0))
	{
		if (game->matrix[y][x - 1] == 'E')
		{
			free_all(game);
			ft_exit("You win!\n");
		}
		if (game->matrix[y][x - 1] == 'C')
			game->img->collectible_count--;
		game->matrix[y][x] = '0';
		game->matrix[y][x - 1] = 'P';
		game->img->move++;
		game->img->player_x -= 1;
	}
}
