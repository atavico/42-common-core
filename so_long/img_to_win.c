/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_to_win.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 17:43:02 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 16:10:15 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"so_long.h"

void	img_to_win(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			if (game->matrix[i][j] != '1' && game->matrix[i][j] != '0' \
				&& game->matrix[i][j] != 'C' && game->matrix[i][j] != 'E' \
				&& game->matrix[i][j] != 'P')
				ft_exit("invalid map\n");
			j++;
		}
		i++;
	}
}

int	place_map(t_game *game)
{
	int		i;
	int		j;
	char	*str;

	mlx_clear_window(game->mlx, game->mlx_win);
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			draw(game, i, j);
			j++;
		}
		i++;
	}
	game->img->frame++;
	if (game->img->frame == 160)
		game->img->frame = 0;
	mlx_string_put(game->mlx, game->mlx_win, 0, 16, 0xc1ffc1, "Moves: ");
	str = ft_itoa(game->img->move);
	mlx_string_put(game->mlx, game->mlx_win, 70, 16, 0xc1ffc1, str);
	free(str);
	return (0);
}
