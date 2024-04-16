/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 14:49:06 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 14:58:36 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

void    ft_check_fd(char *file_name, char *str)
{
    int fd;

    fd = open(file_name, O_RDONLY);
    if(fd <= 0)
    {
        ft_printf("%s ", str);
        ft_error("file");
    }
    close(fd);
}

void ft_check_file(char *file_name)
{
    if(ft_strlen(file_name) < 5)
        ft_error("Map name");
    if(ft_memcmp(&file_name[ft_strlen(file_name) - 4], ".cub", 4) != 0)
        ft_error("Map extencion");
    ft_check_fd(file_name, "Map");
}

void ft_check_info(t_cube3D *data)
{
    if(data->map.NO == NULL || data->map.SO == NULL || data->map.WE == NULL)
        ft_error("Info");
    if(data->map.EA == NULL || data->C < 0 || data->F < 0)
        ft_error("Info");
    ft_check_fd(data->map.NO, "Texture1");
    ft_check_fd(data->map.SO, "Texture2");
    ft_check_fd(data->map.WE, "Texture3");
    ft_check_fd(data->map.EA, "Texture4");
    if(data->map.DO)
        ft_check_fd(data->map.DO, "Texture");
}

void	ft_check_color(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 0 && str[i] != ',')
			ft_error("Color");
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		ft_error("Color");
}