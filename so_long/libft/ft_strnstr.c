/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:04:55 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 18:18:27 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		a;

	i = 0;
	j = 0;
	a = 0;
	if (needle[0] == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < len)
	{
		if (haystack[i++] == needle[j] && needle[j] != 0)
			j++;
		else if (haystack[i] != needle[j])
		{
			j = 0;
			a++;
			i = a;
		}
		if (j == (int)ft_strlen(needle))
			return (((char *)haystack) + i - j);
	}
	return (0);
}
