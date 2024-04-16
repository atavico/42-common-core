/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:19:18 by atarsi            #+#    #+#             */
/*   Updated: 2022/05/11 17:14:02 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_strlen1(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

void	check_width(t_game *game, int width1, char *str, int fd)
{
	while (str)
	{
		width1 = ft_strlen1(str);
		if (game->width != width1)
		{
			if (str != NULL)
				free(str);
			ft_exit("error\n");
		}
		free(str);
		str = get_next_line(fd);
		game->height++;
	}
}

int	read_map(t_game *game, char *filename)
{
	int		fd;
	int		width1;
	char	*str;

	width1 = 0;
	game->height = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	str = get_next_line(fd);
	game->width = ft_strlen1(str);
	check_width(game, width1, str, fd);
	close(fd);
	game->matrix = malloc(sizeof(char *) * game->height + 1);
	game->matrix[game->height] = NULL;
	alloc_matrix(game, filename);
	return (1);
}

void	alloc_matrix(t_game *game, char *filename)
{
	int		fd;
	int		i;
	int		j;
	char	*line;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < game->height)
	{
		game->matrix[i] = malloc(sizeof(char) * game->width + 1);
		j = 0;
		line = get_next_line(fd);
		while (j < game->width)
		{
			game->matrix[i][j] = line[j];
			j++;
		}
		free(line);
		game->matrix[i][game->width] = '\0';
		i++;
	}
	close(fd);
}
