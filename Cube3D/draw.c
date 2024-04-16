/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:39:04 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 15:06:09 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	get_orientation(t_cube3D *data, float x, float y, float rayangle)
{
	if (data->map.map[(int)(y + 0.005)][(int)x] != '1' && (data->map.map[(int)y][(int)(x - 0.005)] == '1' || data->map.map[(int)y][(int)(x + 0.005)] == '1') && data->p.y > y)
		return (1);
	if (data->map.map[(int)(y - 0.005)][(int)x] != '1' && (data->map.map[(int)y][(int)(x - 0.005)] == '1' || data->map.map[(int)y][(int)(x + 0.005)] == '1') && data->p.y < y)
		return (2);//sud
	if (data->map.map[(int)y][(int)(x + 0.005)] != '1' && (data->map.map[(int)(y - 0.005)][(int)x] == '1' || data->map.map[(int)(y + 0.005)][(int)x] == '1') && data->p.x > x)
		return (3);//ovest
	if (data->map.map[(int)y][(int)(x - 0.005)] != '1' && (data->map.map[(int)(y - 0.005)][(int)x] == '1' || data->map.map[(int)(y + 0.005)][(int)x] == '1') && data->p.x < x)
		return (4);//est
	if (rayangle < 0.5 || rayangle > 5)
		return (4);
	if (rayangle >= 0.5 && rayangle < 2)
		return (2);
	if (rayangle >= 2 && rayangle < 3.5)
		return (3);
	if (rayangle >= 3.5 && rayangle < 5)
		return (1);
	return (0);
}

void    ft_render_game(t_cube3D *data, t_ray *r, int orientation)
{
    r->r_dist = r->dist;
    int     y;
    
    if(r->dist < 1)
        r->dist = 1;
    r->wall = (data->s_h / 2) / r->dist;
    y = -1;
    while(++y < ((data->s_h / 2) - r->wall))
        my_pixel_put(data->screen, r->w_x, y, data->C);
    y--;
    while(++y < ((data->s_h / 2) + r->wall))
    {
        if (orientation == 1)
	    	text_pixel_put(data, r, &y, data->north);
	    else if (orientation == 2)
	    	text_pixel_put(data, r, &y, data->east);
	    else if (orientation == 3)
	    	text_pixel_put(data, r, &y, data->west);
	    else if (orientation == 4)
	    	text_pixel_put(data, r, &y, data->south);
	    else if (orientation == 5)
	    	text_pixel_put(data, r, &y, data->door);
	    else if (orientation == 6)
	    	text_pixel_put(data, r, &y, data->door2);
    }
    y--;
    while(++y < data->s_h)
        my_pixel_put(data->screen, r->w_x, y, data->F);
}

void ft_traceray(float rayangle, t_cube3D *data, const int x)
{
    float   cos_ray;
    float   sin_ray;
    t_ray   r;

    r.w_x = x;
    cos_ray = cos(rayangle) / 256;
    sin_ray = sin(rayangle) / 256;
    r.x = data->p.x;
    r.y = data->p.y;

    while(data->map.map[(int)r.y][(int)r.x] != '1' && data->map.map[(int)r.y][(int)r.x] != 'D')
    {
        r.x += cos_ray;
        r.y += sin_ray;
        //my_pixel_put(data->minimap, (int)(r.x * data->cellsize), (int)(r.y * data->cellsize), 16449536);
    }
    r.dist = sqrt(powf(data->p.x - r.x, 2) + powf(data->p.y - r.y, 2));
    r.dist *= cos((rayangle - data->p.angle)); //ottimizzazone eliminazione fish-eye
    ft_render_game(data, &r, get_orientation(data, r.x, r.y, rayangle));
}

void ft_raycasting(t_cube3D *data)
{
    float   rayangle;
    float   increment;
    int     i;

    data->ray.dist = 0;
    rayangle = data->p.angle - (FOV_R/2);
    increment = (float)FOV / (float)data->s_w;
    increment *= (PI / 180);
    i = 0;
    while(rayangle < data->p.angle + (FOV_R/2))
    {
        ft_traceray(rayangle, data, i);
        rayangle += increment;
        i++;
    }
}

int    ft_draw(t_cube3D *data)
{
    ft_movements(data);
    ft_draw_minimap(data);
    ft_raycasting(data);
    

    mlx_put_image_to_window(data->mlx, data->win, data->screen.img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->minimap.img, 0, 0);
    return(0);
}