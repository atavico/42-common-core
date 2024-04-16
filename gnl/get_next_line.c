/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 14:08:04 by atarsi            #+#    #+#             */
/*   Updated: 2022/03/15 20:04:08 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*str;
	static char	*save;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	str = save;
	while (ft_strchr(str, '\n') == 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buffer[bytes] = '\0';
		str = ft_strjoin(str, buffer);
		if (bytes < BUFFER_SIZE)
			break ;
	}
	free(buffer);
	save = ft_save(str);
	return (str);
}

char	*ft_save(char *str)
{
	char		*ret;
	int			i;
	int			j;

	if (ft_strchr(str, '\n') == 0)
		return (NULL);
	i = 0;
	while (str[i] != '\n')
		i++;
	i += 1;
	j = 0;
	while (str[i + j] != '\0')
		j++;
	if (j == 0)
		return (NULL);
	ret = (char *)malloc(sizeof(char ) * j + 1);
	if (!ret)
		return (NULL);
	ft_strcpy(str, ret, i);
	return (ret);
}

void	ft_strcpy(char *str, char *ret, int i)
{
	int	j;

	j = 0;
	while (str[i + j] != '\0')
	{	
		ret[j] = str[i + j];
		j++;
	}
	str[i] = '\0';
	ret[j] = '\0';
}
