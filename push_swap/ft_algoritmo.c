/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algoritmo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 19:10:22 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/13 19:42:37 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_search_rot(t_a *data)
{
	while (data->a[0] != 1)
	{
		if (ft_find(data->a, 1) <= data->size_a / 2)
			rot_a(data);
		else
			re_rot_a(data);
	}
}

void	ft_algoritmo(t_a *data)
{
	while (data->size_b != 0)
	{
		data->ptr = ft_countmoves(data);
		while (data->b[0] != data->ptr.n_b && data->ptr.dir_b == 0 && \
				data->a[0] != data->ptr.n_a && data->ptr.dir_a == 0)
			rot_r(data);
		while (data->b[0] != data->ptr.n_b && data->ptr.dir_b == 1 && \
				data->a[0] != data->ptr.n_a && data->ptr.dir_a == 1)
			re_rot_r(data);
		while (data->b[0] != data->ptr.n_b && data->ptr.dir_b == 0)
			rot_b(data);
		while (data->b[0] != data->ptr.n_b && data->ptr.dir_b == 1)
			re_rot_b(data);
		while (data->a[0] != data->ptr.n_a && data->ptr.dir_a == 0)
			rot_a(data);
		while (data->a[0] != data->ptr.n_a && data->ptr.dir_a == 1)
			re_rot_a(data);
		push_a(data);
	}
	ft_search_rot(data);
}
