/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 02:23:11 by marvin            #+#    #+#             */
/*   Updated: 2022/05/10 02:23:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	print_stack(int *a, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("%d\n", a[i]);
		i++;
	}
}

int	*ft_intdup(int *array, int size)
{
	int	i;
	int	*array2;

	array2 = malloc (sizeof(int) * size);
	i = 0;
	while (i < size)
	{
		array2[i] = array[i];
		i++;
	}
	return (array2);
}

int	ft_find(int *array, int num)
{
	int	i;

	i = 0;
	while (array[i] != num)
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	free_matrix(void *matrix[], int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free (matrix[i]);
		i++;
	}
	free(matrix);
}
