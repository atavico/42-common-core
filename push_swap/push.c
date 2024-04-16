/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:37:30 by marvin            #+#    #+#             */
/*   Updated: 2022/05/10 02:37:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push(int *ar_a, int *ar_b, int *size_a, int *size_b)
{
	int	i;

	if (*size_a == 0)
		ft_exit ("error\n");
	i = *size_b;
	while (i > 0)
	{
		ar_b[i] = ar_b[i - 1];
		i--;
	}
	ar_b[0] = ar_a[0];
	*size_b += 1;
	i = 0;
	while (i < *size_a - 1)
	{
		ar_a[i] = ar_a[i + 1];
		i++;
	}
	*size_a -= 1;
}

void	push_a(t_a *data)
{
	push (data->b, data->a, &data->size_b, &data->size_a);
	ft_putstr_fd ("pa\n", 1);
}

void	push_b(t_a *data)
{
	push (data->a, data->b, &data->size_a, &data->size_b);
	ft_putstr_fd ("pb\n", 1);
}
