/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 13:12:42 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 17:06:28 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	dest = (char *)malloc(sizeof(*s1) * (s1_len + s2_len + 1));
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, s1_len);
	dest += s1_len;
	ft_memcpy(dest, s2, s2_len);
	dest -= s1_len;
	dest[s1_len + s2_len] = '\0';
	return (dest);
}
