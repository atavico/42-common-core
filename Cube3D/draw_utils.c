/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 15:07:47 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 15:07:41 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	gettextcolor(int x, int y, t_texture text)
{
	int		color;
	char	*dst;

	dst = text.addr + (y * text.l_bytes + x * (text.bfp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	my_pixel_put(t_image s_image, int x, int y, int color)
{
	char	*dst;

	dst = s_image.addr + (y * s_image.l_bytes + x * (s_image.bfp / 8));
	*(unsigned int *)dst = color;
}

void ft_draw_cell(t_cube3D *data, int x, int y, int c)
{
    int i;
    int j;

    i = 0;
    while(i < data->cellsize)
    {
        j = 0;
        while(j < data->cellsize)
        {
            my_pixel_put(data->minimap, x + j, y + i, c);
            j++;
        }
    i++;
    }
}

void    ft_draw_player(t_cube3D *data, int x, int y)
{
    int	i;
	int	j;

	i = y - data->cellsize / 8;
    while(i <= (y + data->cellsize / 8))
    {
        j = x - data->cellsize / 8;
        while(j <= (x + data->cellsize / 8))
        {
            my_pixel_put(data->minimap, (int)j, (int)i, 16449536);
            j++;
        }
        i++;
    }
}

void    ft_draw_minimap(t_cube3D *data)
{
    int i = 0;
    int j;
    while (data->map.map[i] != NULL)
    {
        j = 0;
        while(data->map.map[i][j] != '\0')
        {
            if (data->map.map[i][j] == '1')
                ft_draw_cell(data, j * data->cellsize, i * data->cellsize, 200);
            else
                ft_draw_cell(data, j * data->cellsize, i * data->cellsize, 0);
            j++;
        }
        i++;
    ft_draw_player(data, data->p.x * data->cellsize, data->p.y * data->cellsize);
    }
}
