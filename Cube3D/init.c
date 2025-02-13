/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:08:51 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 14:59:38 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_init_image(t_cube3D *data)
{
    data->cH_size = (data->s_h / 2 / data->row);
    data->cW_size = (data->s_w / 2 / data->col);
    if (data->cW_size < data->cH_size)
        data->cellsize = data->cW_size;
    else
        data->cellsize = data->cH_size;
    data->map.mm_H = data->row * data->cellsize;
    data->map.mm_W = data->col * data->cellsize;
    data->screen.img = mlx_new_image(data->mlx, data->s_w, data->s_h);
    data->screen.addr = mlx_get_data_addr(data->screen.img, &data->screen.bfp, &data->screen.l_bytes, &data->screen.endian);
    data->minimap.img = mlx_new_image(data->mlx, data->map.mm_W, data->map.mm_H);
	data->minimap.addr = mlx_get_data_addr(data->minimap.img, &data->minimap.bfp, &data->minimap.l_bytes, &data->minimap.endian);
    ft_init_texture(data);
}

void ft_init_info(t_cube3D *data)
{
    data->map.NO = NULL;
    data->map.SO = NULL;
    data->map.EA = NULL;
    data->map.WE = NULL;
    data->map.DO = NULL;
    data->F = -1;
    data->C = -1;
}

void    ft_init_player(t_cube3D *data, char c)
{
    if(c == 'S')
        data->p.angle = PI/2;
    else if(c == 'E')
        data->p.angle = 0;
    else if(c == 'W')
        data->p.angle = PI;
    else if(c == 'N')
        data->p.angle = (3 * PI)/2;
}

void ft_find_p(t_cube3D *data)
{
    char c;
    int row;
    int col;

    row = 0;
    while(data->map.map[row] != NULL)
    {
        col = 0;
        while(data->map.map[row][col] != '\0')
        {
            c = data->map.map[row][col];
            if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
            {
                ft_init_player(data, c);
                data->p.x = col + 0.5;
                data->p.y = row + 0.5;
            }
            col++;
        }
        row++;
    }
}

void    ft_init(t_cube3D *data)
{
    ft_find_p(data);
    data->p.w = 0;
    data->p.a = 0;
    data->p.s = 0;
    data->p.d = 0;
    data->ray.w_x = 0;
    data->p.rigth = 0;
    data->p.left = 0;
    data->cH_size = 0;
    data->cW_size = 0;
    data->map.mm_H = 0;
    data->map.mm_W = 0;
    data->cellsize = 0;
    data->s_h = HEIGHT;
    data->s_w = WEIGHT;
    data->p.dx = cos(data->p.angle);
    data->p.dy = sin(data->p.angle);
    data->mlx = mlx_init();
    // mlx_get_screen_size(data->mlx, &data->s_h, &data->s_w);
    // printf("%d %d\n", data->s_h, data->s_w);
    data->win = mlx_new_window(data->mlx, data->s_w, data->s_h, "cub3D");
    ft_init_image(data);
}