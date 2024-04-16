/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:38:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 14:55:17 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

t_texture   ft_assign_text(char *path, t_cube3D *data)
{
    t_texture   ret;
    
    ret.ptr = mlx_xpm_file_to_image(data->mlx, path, &ret.width, &ret.height);
    if (!ret.ptr)
		ft_error("Unvalid texture");
	ret.addr = mlx_get_data_addr(ret.ptr, &ret.bfp, &ret.l_bytes, &ret.endian);
	return (ret);
}

void    ft_init_texture(t_cube3D *data)
{
    data->north = ft_assign_text(data->map.NO, data);
    data->south = ft_assign_text(data->map.SO, data);
    data->west = ft_assign_text(data->map.WE, data);
    data->east = ft_assign_text(data->map.EA, data);
    
}

int	printwallpixel(t_ray *ray, t_texture text, int itexture)
{
	int	textx;

	textx = (((ray->x + ray->y) * 64.0)
			- ((int)(ray->x + ray->y) * 64));
	return (gettextcolor(textx, itexture, text));
}

void	gettextstart(t_cube3D *data, t_ray *ray, float *yincrementer, int *itexture)
{
	int	wheigt;

	wheigt = data->s_h / 2 / ray->r_dist;
	*yincrementer = (wheigt * 2) / 64.0;
	if (ray->r_dist >= 1)
	{
		*itexture = 0;
		return ;
	}
	*itexture = (wheigt - data->s_h / 2) / *yincrementer;
	*yincrementer = (ray->wall * 2) / (64.0 - (*itexture) * 2);
}

void	text_pixel_put(t_cube3D *data, t_ray *r, int *y, t_texture text)
{
	float	d;
	float	yincrementer;
	int		itexture;

	gettextstart(data, r, &yincrementer, &itexture);
	if (*y == -1)
		(*y)++;
	d = *y;
	while (*y < data->s_h / 2 + r->wall)
	{
		d += yincrementer;
		while (*y <= d)
		{
			my_pixel_put(data->screen, r->w_x, *y, printwallpixel(r, text, itexture));
			(*y)++;
		}
		itexture++;
	}
}