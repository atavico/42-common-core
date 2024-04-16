/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:40:08 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 15:08:44 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_read_file(char *file_name, t_cube3D *data)
{
    int     fd;
    char    *str;
    char    **matrix = NULL;


    data->row = 0;
    data->col = 0;
    ft_init_info(data);
    fd = open(file_name, O_RDONLY);
    ft_get_info(data, fd);
    ft_check_info(data);
    close(fd);
    fd = open(file_name, O_RDONLY);
    str = ft_find_map(fd);
    data->map.map = ft_fill_map(str, matrix, fd, file_name);
    ft_map_size(data);
    ft_check_map(data->map.map);
    close(fd);
}

int main(int argc, char *argv[])
{
    t_cube3D data;

    if(argc != 2)
        ft_error("Arg");
    ft_check_file(argv[1]);
    ft_read_file(argv[1], &data);
    ft_init(&data);
	mlx_hook(data.win, 2, 1L << 0, ft_on, &data);
	mlx_hook(data.win, 3, 1L << 0, ft_off, &data);
	//mlx_hook(data.win, 17, 1L << 17, ft_exit, &data);
    mlx_loop_hook(data.mlx, ft_draw, &data);
    mlx_loop(data.mlx);
	ft_free_struct(&data);
    return (0);
}