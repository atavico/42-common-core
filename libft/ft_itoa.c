/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/16 20:04:32 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/17 15:56:07 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_ptnbr(long n, char *str, size_t len)
{
	int	sign;

	sign = 0;
	if (n < 0)
	{
		sign++;
		n *= -1;
	}
	while (--len)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	else
		str[len] = n % 10 + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nbr;
	size_t	len;

	nbr = n;
	if (nbr == 0)
		return (str = ft_strdup("0"));
	len = ft_count(nbr);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = 0;
	ft_ptnbr(nbr, str, len);
	return (str);
}
