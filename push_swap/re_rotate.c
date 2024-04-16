/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_rotate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:10:44 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/11 19:08:12 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	re_rotate(int *array, int size)
{
	int	i;
	int	tmp;

	i = size - 1;
	tmp = array[i];
	while (i > 0)
	{
		array[i] = array[i - 1];
		i--;
	}
	array[0] = tmp;
}

void	re_rot_a(t_a *data)
{
	re_rotate(data->a, data->size_a);
	ft_putstr_fd ("rra\n", 1);
}

void	re_rot_b(t_a *data)
{
	re_rotate(data->b, data->size_b);
	ft_putstr_fd ("rrb\n", 1);
}

void	re_rot_r(t_a *data)
{
	re_rotate (data->a, data->size_a);
	re_rotate (data->b, data->size_b);
	ft_putstr_fd ("rrr\n", 1);
}
