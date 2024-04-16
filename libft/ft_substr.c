/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:40:48 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 16:49:07 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rslt;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	rslt = (char *)malloc(sizeof(*s) * (len + 1));
	if (!rslt)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
		{
			rslt[j] = s[i];
			j++;
		}
		i++;
	}
	rslt[j] = 0;
	return (rslt);
}
