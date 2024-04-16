/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:08:02 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/13 14:08:49 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;
	char	*st;

	i = 0;
	st = ((char *) b);
	while (i < len)
	{
		st[i] = ((char) c);
		i++;
	}
	return (b);
}
