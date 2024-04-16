/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:43:32 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 17:10:23 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	take_bott(int botton, t_game *game)
{
	if (botton == 53)
	{
		mlx_clear_window(game->mlx, game->mlx_win);
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit (0);
	}
	else if (botton == 13)
		move_up(game);
	else if (botton == 1)
		move_down(game);
	else if (botton == 0)
		move_left(game);
	else if (botton == 2)
		move_right(game);
	place_map(game);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_game	game;
	t_img	img;

	if (argc != 2)
		ft_exit("error\ninvalid map\n");
	if (!read_map(&game, argv[1]))
		ft_exit("error\nNo valid file\n");

	game.mlx = mlx_init();
	game.img = &img;
	if (!check_validity(&game))
	{
		free_all(&game);
		ft_exit("error\nNo valid map\n");
	}
	init_images(&game);
	game.mlx_win = mlx_new_window(game.mlx, (game.width) * 64, \
					(game.height) * 64, "so_long");
	img_to_win(&game);
	img.move = 0;
	mlx_key_hook(game.mlx_win, take_bott, &game);
	mlx_loop_hook(game.mlx, place_map, &game);
	mlx_hook(game.mlx_win, 17, 0, ft_exit, 0);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}
