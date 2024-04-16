/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:17:22 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 15:07:59 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void ft_map_size(t_cube3D *data)
{
    int row;
    int col;

    row = 0;
    while(data->map.map[row] != NULL)
    {
        col = 0;
        while(data->map.map[row][col] != '\0')
        {
           
            col++;
            if (col > data->col)
                data->col = col;
        }
        row++;
    }
    data->row = row;
}

int ft_skip_space(char *str)
{
    int i;

    i = 0;
    while(ft_isspace(str[i]) == 1)
        i++;
    return (i);
}

char *ft_find_map(int fd)
{
    char    *str;
    int     i;

    str = get_next_line(fd);
    while(str != NULL)
    {
        i = 0;
        while(ft_isspace(str[i]) == 1)
            i++;
        if(str[i] == '1')
        {
            
            return (str);
        }
        free(str);
        str = get_next_line(fd);
    }
    ft_error("Map");
    return (0);
}

// int ft_exit(t_cube3D *data)
// {
//     t_cube3D data;
// 	exit(0);
// }

void	ft_free_struct(t_cube3D *data)
{
	free(data->map.NO);
	free(data->map.SO);
	free(data->map.WE);
	free(data->map.EA);
	ft_free_matrix((void **)data->map.map);
}
