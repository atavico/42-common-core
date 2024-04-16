/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:10:36 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 14:09:38 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*csrc;
	char	*cdest;
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	csrc = ((char *)src);
	cdest = ((char *)dst);
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dst);
}
