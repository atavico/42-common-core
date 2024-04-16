/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:12:15 by atarsi            #+#    #+#             */
/*   Updated: 2022/01/13 11:12:18 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char str)
{
	if ((str >= 9 && str <= 13) || str == 32)
		return (1);
	return (0);
}

static void	calc_sign(const char *str, int *i, int *sign)
{
	if (str[*i] == 43)
	{
		*i += 1;
		return ;
	}
	if (str[*i] == 45)
	{
		*sign *= -1;
		*i += 1;
	}
}

static void	get_int(const char *str, int j, int sign, int *nb)
{
	int	a;

	*nb = 0;
	while (str[j] >= 48 && str[j] <= 57)
	{
		a = (str[j] - '0') * sign;
		*nb = *nb * 10 + a;
		j++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	nb;

	sign = 1;
	i = 0;
	if (str[0] == 0)
		return (0);
	while (is_space(str[i]))
		i++;
	calc_sign(&str[0], &i, &sign);
	get_int(&str[0], i, sign, &nb);
	return (nb);
}
