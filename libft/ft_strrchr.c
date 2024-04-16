/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:04:20 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 16:14:16 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*res;
	int		temp_index;
	char	ch;

	ch = c;
	i = 0;
	len = 0;
	temp_index = -1;
	while (s[len] != 0)
		len++;
	while (i < len + 1)
	{
		if (s[i] == ch)
			temp_index = i;
		i++;
	}
	res = (char *)&s[temp_index];
	if (temp_index == -1)
		return (NULL);
	else
		return (res);
}
