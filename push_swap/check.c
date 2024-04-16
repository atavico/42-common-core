/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:08:42 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/08 17:43:23 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_checkmalloc(void	*ptr)
{
	if (ptr == NULL)
		ft_exit ("error\n");
}

void	ft_checkdigit(t_a *struct_a, char **matrix)
{
	int	i;
	int	j;

	i = 0;
	while (i < struct_a->size_a)
	{
		j = 0;
		if (matrix[i][j] == '+' || matrix [i][j] == '-')
			j++;
		if (matrix[i][j] == '\0')
			ft_exit ("error\n");
		while (matrix[i][j] != '\0')
		{
			if (!ft_isdigit(matrix[i][j]))
				ft_exit ("error\n");
			j++;
		}
		i++;
	}
}

void	ft_checkdouble(t_a *struct_a, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (struct_a->a[i] == struct_a->a[j])
			{
				free (struct_a->a);
				free (struct_a->b);
				ft_exit ("error\n");
			}
			j++;
		}
		i++;
	}
}

int	ft_order(int *ar, int size)
{
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (ar[i] > ar[i + 1])
			return (0);
		i++;
	}
	return (1);
}
