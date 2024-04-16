/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 17:26:35 by atarsi            #+#    #+#             */
/*   Updated: 2022/04/30 15:55:36 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_exit(char *str)
{
	ft_putstr_fd(str, 0);
	exit(0);
}

void	free_all(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->height)
	{
		free(game->matrix[i]);
		i++;
	}
	free (game->matrix);
}
