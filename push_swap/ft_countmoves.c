/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countmoves.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:30:12 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/11 18:27:36 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_find_n_a_1(t_a *data, t_moves *count, int i, int x)
{
	if (i == data->size_a)
	{
		count->n_a = 1;
		if (x <= data->size_a / 2)
			count->dir_a = 0;
		else
			count->dir_a = 1;
		count->ind_a = x;
	}
	else
	{
		count->ind_a = i;
		if (i <= data->size_a / 2)
			count->dir_a = 0;
		else
			count->dir_a = 1;
		count->n_a = data->a[i];
	}
}

void	ft_find_n_a(t_a *data, t_moves *count, int nb)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = data->size_a - 1;
	while (i < data->size_a)
	{
		if (data->a[i] == 1)
			x = i;
		if (data->a[j] < nb && data->a[i] > nb)
			break ;
		if (j == data->size_a - 1)
			j = -1;
		j++;
		i++;
	}
	ft_find_n_a_1 (data, count, i, x);
}

t_moves	ft_best(t_moves *count, int size)
{
	int		i;
	t_moves	min;

	min = count[0];
	i = 1;
	while (i < size)
	{
		if (min.moves > count[i].moves)
			min = count[i];
		i++;
	}
	free (count);
	return (min);
}

void	ft_dir(t_a *data, t_moves *count, int i)
{
	if (count[i].dir_a == 0 && count[i].dir_b == 0)
	{
		if (i > count[i].ind_a)
			count[i].moves = i;
		else
			count[i].moves = count[i].ind_a;
	}
	else if (count[i].dir_a == 1 && count[i].dir_b == 0)
		count[i].moves = i + (data->size_a - count[i].ind_a);
	else if (count[i].dir_a == 0 && count[i].dir_b == 1)
		count[i].moves = (data->size_b - i) + count[i].ind_a;
	else if (count[i].dir_a == 1 && count[i].dir_b == 1)
	{
		if ((data->size_b - i) > (data->size_a - count[i].ind_a))
			count[i].moves = (data->size_b - i);
		else
			count[i].moves = (data->size_a - count[i].ind_a);
	}
}

t_moves	ft_countmoves(t_a *data)
{
	t_moves	*count;
	int		i;

	count = malloc (sizeof(t_moves) * data->size_b);
	i = 0;
	while (i < data->size_b)
	{
		count[i].n_b = data->b[i];
		if (i <= data->size_b / 2)
			count[i].dir_b = 0;
		else
			count[i].dir_b = 1;
		ft_find_n_a(data, &count[i], data->b[i]);
		ft_dir(data, count, i);
		i++;
	}
	return (ft_best(count, data->size_b));
}
