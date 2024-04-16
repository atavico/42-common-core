/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:15:31 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/13 20:01:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_bubble(int *array, int size)
{
	int	i;
	int	flag;

	flag = 0;
	while (flag == 0)
	{
		flag = 1;
		i = 0;
		while (i < size - 1)
		{
			if (array[i] > array[i + 1])
			{
				swap(&array[i], &array[i + 1]);
				flag = 0;
			}
			i++;
		}
	}
}

int	*ft_trasformer(int *array, int size)
{
	int	*array2;
	int	i;
	int	j;

	array2 = ft_intdup(array, size);
	ft_bubble(array2, size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			if (array[i] == array2[j])
			{
				array[i] = j + 1;
				break ;
			}
			j++;
		}
		i++;
	}
	free(array2);
	return (array);
}

int	main(int ac, char *av[])
{
	t_a	data;

	if (ac <= 1)
		return (0);
	if (ac >= 2)
	{
		ft_split_str(&data, av, ac);
		data.a = ft_trasformer(data.a, data.size_a);
		if (ft_order(data.a, data.size_a) == 1)
			return (0);
		if (data.a[0] == 1 || data.a[1] == 2 || data.a[2] == 3)
			if (data.a[2] != 5 && data.a[0] != 4)
				swap_a(&data);
		ft_lis(&data);
		ft_search_num(&data);
		ft_algoritmo(&data);
		free(data.lis);
		free (data.a);
		free (data.b);
		return (0);
	}
}
