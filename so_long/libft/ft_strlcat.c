/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:06:45 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/14 15:38:52 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	s_len;
	size_t	d_len;

	i = 0;
	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (dstsize == 0)
		return (s_len);
	while (src[i] != 0 && (d_len + i) < (dstsize - 1))
	{
		dst[d_len + i] = src[i];
		i++;
	}
	if (i != dstsize && d_len < (dstsize - 1))
		dst[d_len + i] = 0;
	if (dstsize > d_len)
		return (s_len + d_len);
	else
		return (s_len + dstsize);
}
