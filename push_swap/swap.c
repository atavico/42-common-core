/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:11:35 by marvin            #+#    #+#             */
/*   Updated: 2022/05/10 02:11:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_a(t_a *data)
{
	swap(&data->a[0], &data->a[1]);
	ft_putstr_fd ("sa\n", 1);
}

void	swap_b(t_a *data)
{
	swap(&data->b[0], &data->b[1]);
	ft_putstr_fd ("sb\n", 1);
}

void	swap_s(t_a *data)
{
	swap(&data->b[0], &data->b[1]);
	swap(&data->a[0], &data->a[1]);
	ft_putstr_fd ("ss\n", 1);
}
