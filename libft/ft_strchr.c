/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:07:07 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 17:54:48 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		len;
	char	ch;

	ch = c;
	len = 0;
	i = 0;
	while (s[len] != 0)
		len++;
	while (i < len + 1)
	{
		if (s[i] == ch)
			return ((char *)&s[i]);
		i++;
	}
	return (0);
}
