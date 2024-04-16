/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 15:14:13 by atarsi            #+#    #+#             */
/*   Updated: 2023/05/22 17:38:40 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data.h"

int	ft_get_color(char *str)
{
	char	**matrix;
	int		color;
	int		i;

	ft_check_color(str);
	matrix = ft_split(str, ',');
	color = 0;
	i = 0;
	while (matrix[i] != NULL)
	{
	    if (ft_atoi(matrix[i]) < 0 || ft_atoi(matrix[i]) > 255)
			ft_error("Color");
		else if (i == 0)
			color += ft_atoi(matrix[i]) * 65536;
		else if (i == 1)
			color += ft_atoi(matrix[i]) * 256;
		else
			color += ft_atoi(matrix[i]);
		i++;
	}
	free(str);
	ft_free_matrix((void **) matrix);
	if (i != 3)
		ft_error("Color");
	return (color);
}

char *ft_fill_info(char *str)
{
    char    *tmp;
    int     i;
    int     j;

    i = 0;
    while(ft_isspace(str[i]) == 1)
        i++;
    j = 0;
    while(ft_isspace(str[i + j]) == 0)
        j++;
    str[i + j] = '\0';
    tmp = (char *) malloc (sizeof(char) * (j + 1));
    ft_check_malloc(tmp);
    j = 0;
    while(str[i + j] != '\0')
    {
        tmp[j] = str[i + j];
        j++;
    }
    tmp[j] = '\0';
    return (tmp);
}

int ft_parse_info(t_cube3D *data, char *str)
{   
    if(ft_memcmp(str, "NO", 2) == 0 && data->map.NO == NULL)
        data->map.NO = ft_fill_info(str + 2);
    else if(ft_memcmp(str, "SO", 2) == 0 && data->map.SO == NULL)
        data->map.SO = ft_fill_info(str + 2);
    else if(ft_memcmp(str, "WE", 2) == 0 && data->map.WE == NULL)
        data->map.WE = ft_fill_info(str + 2);
    else if(ft_memcmp(str, "EA", 2) == 0 && data->map.EA == NULL)
        data->map.EA = ft_fill_info(str + 2);
    // else if(ft_memcmp(str, "DO", 2) == 0 && data->DO == NULL)
    //     data->map.DO = ft_fill_info(str + 2);
    else if(*str == 'F' && data->F == -1)
       data->F = ft_get_color(ft_fill_info(str + 1));
    else if(*str == 'C' && data->C == -1)
       data->C = ft_get_color(ft_fill_info(str + 1));
    else
        return(0);
    return (1);        
}

void    ft_get_info(t_cube3D *data, int fd)
{
    char    *str;
    int     i;

    i = 0;
    str = get_next_line(fd);
    while(str != NULL)
    {
        i = ft_skip_space(str);
        if (str[i] == '1')
        {
            free(str);
            break ;
        }
        if (str[i] != '\0')
            if(ft_parse_info(data, str + i) == 0)
                ft_error("info");
        free(str);
        str = get_next_line(fd);
    }
}

char **ft_fill_map(char *str, char **matrix, int fd, char *file_name)
{
    int i;

    i = 0;
    while (str != NULL)
    {
        i++;
        free(str);
        str = get_next_line(fd);
    }
    close(fd);
    matrix = (char **) malloc (sizeof(char *) * (i + 1));
    ft_check_malloc(matrix);
    fd = open(file_name, O_RDONLY);
    str = ft_find_map(fd);
    i = 0;
    while(str != NULL)
    {
        if(str[i]=='\n')
           str[i]='\0';
        printf("%s %d\n", str, i);
        matrix[i] = str;
        str = get_next_line(fd);
        i++;
    }
    close(fd);
    return(matrix);
}