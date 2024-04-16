/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:53:33 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/11 19:10:33 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(int *array, int size)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = array[i];
	while (i < (size - 1))
	{
		array[i] = array[i + 1];
		i++;
	}
	array[size - 1] = tmp;
}

void	rot_a(t_a *data)
{
	rotate (data->a, data->size_a);
	ft_putstr_fd ("ra\n", 1);
}

void	rot_b(t_a *data)
{
	rotate (data->b, data->size_b);
	ft_putstr_fd ("rb\n", 1);
}

void	rot_r(t_a *data)
{
	rotate (data->a, data->size_a);
	rotate (data->b, data->size_b);
	ft_putstr_fd ("rr\n", 1);
}
