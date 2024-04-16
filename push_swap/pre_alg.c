/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_alg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:16:18 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/13 19:36:50 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_push_away(t_a *data, int nb, int i)
{
	while (data->a[0] != nb && i <= data->size_a)
		rot_a(data);
	while (data->a[0] != nb && i > data->size_a)
		re_rot_a(data);
	push_b(data);
}

void	ft_search_num2(int *med, t_a *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->size_a)
	{
		j = 0;
		while (j < data->size_lis)
		{
			if (data->a[i] == data->lis[j])
				break ;
			j++;
		}
		if (j == data->size_lis && (data->a[i] <= (*med) || (*med) < 3))
		{
			ft_push_away(data, data->a[i], i);
			i = -1;
		}
		i++;
	}
	(*med) += (data->size_a + data->size_b) / 4;
}

void	ft_search_num(t_a *data)
{
	int	med;

	med = data->size_a / 4;
	while (data->size_a != data->size_lis && med != 0)
		ft_search_num2(&med, data);
}
