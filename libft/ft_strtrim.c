/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 15:35:15 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/20 17:07:56 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	check_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}	
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	k;
	size_t	j;

	if (!s1 || !set)
		return (NULL);
	k = 0;
	while (check_set(s1[k], (char *)set))
		k++;
	j = ft_strlen(s1);
	while (check_set(s1[j - 1], (char *)set) && j > k)
		j--;
	return (ft_substr((char *) s1, k, j - k));
}
