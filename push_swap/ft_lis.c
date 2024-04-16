/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 17:50:11 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/13 20:01:03 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int	*ft_lis_case2(int *str_1, int s_lis, int nb)
// {
// 	int	j;
// 	int	*str;

// 	str = malloc (sizeof(int) * s_lis + 1);
// 	j = 0;
// 	while (j < s_lis)
// 	{
// 		str[j] = str_1[j];
// 		j++;
// 	}
// 	str[j] = nb;
// 	return (str);
// }

// void	ft_lis_case3(int s_lis, int **matrix, int nb)
// {
// 	int	j;
// 	int	x;

// 	j = 0;
// 	while (j < s_lis)
// 	{
// 		if (matrix[j][j] > nb)
// 			break ;
// 		j++;
// 	}
// 	x = 0;
// 	while (x < j)
// 	{
// 		matrix[j][x] = matrix[j - 1][x];
// 		x++;
// 	}
// 	matrix[j][j] = nb;
// }

// void	ft_3case_lis(t_a *data, int **matrix, int s_lis, int i)
// {
// 	if (data->a[i] > matrix[s_lis - 1][s_lis - 1])
// 	{
// 		matrix[s_lis] = ft_lis_case2(matrix[s_lis - 1], s_lis, data->a[i]);
// 		s_lis += 1;
// 	}
// 	else if (data->a[i] < matrix[s_lis -1][s_lis -1])
// 		ft_lis_case3(s_lis, matrix, data->a[i]);
// }

// void	ft_lis(t_a *data)
// {
// 	int	**matrix;
// 	int	i;
// 	int	x;
// 	int	s_lis;

// 	matrix = malloc (sizeof (int *) * data->size_a);
// 	matrix[0] = malloc (sizeof(int) * 1);
// 	x = ft_find(data->a, 1);
// 	matrix[0][0] = data->a[x];
// 	i = x + 1;
// 	if (i == data->size_a)
// 		i = 0;
// 	s_lis = 1;
// 	while (i != x)
// 	{
// 		ft_3case_lis(data, matrix, s_lis, i);
// 		i++;
// 		if (i == data->size_a)
// 			i = 0;
// 	}
// 	data->size_lis = s_lis;
// 	data->lis = ft_intdup(matrix[s_lis - 1], s_lis);
// 	free_matrix((void **)matrix, s_lis);
// }

int	*ft_case2(int *str_1, int *s_lis, int nb)
{
	int	j;
	int	*str;

	str = malloc (sizeof(int) * *s_lis + 1);
	j = 0;
	while (j < *s_lis)
	{
		str[j] = str_1[j];
		j++;
	}
	str[j] = nb;
	*s_lis += 1;
	return (str);
}

void	ft_case3(int s_lis, int **matrix, int nb)
{
	int	j;
	int	x;

	j = 0;
	while (j < s_lis)
	{
		if (matrix[j][j] > nb)
			break ;
		j++;
	}
	x = 0;
	while (x < j)
	{
		matrix[j][x] = matrix[j - 1][x];
		x++;
	}
	matrix[j][j] = nb;
}

void	ft_lis(t_a *data)
{
	int	**matrix;
	int	i;
	int	s_lis;

	matrix = malloc (sizeof (int *) * data->size_a);
	matrix[0] = malloc (sizeof(int) * 1);
	matrix[0][0] = data->a[ft_find(data->a, 1)];
	i = ft_find(data->a, 1) + 1;
	if (i == data->size_a)
		i = 0;
	s_lis = 1;
	while (data->a[i] != 1)
	{
		if (data->a[i] > matrix[s_lis - 1][s_lis - 1])
			matrix[s_lis - 1] = ft_case2(matrix[s_lis - 1], &s_lis, data->a[i]);
		else if (data->a[i] < matrix[s_lis -1][s_lis -1])
			ft_case3(s_lis, matrix, data->a[i]);
		i++;
		if (i == data->size_a)
			i = 0;
	}
	data->size_lis = s_lis;
	data->lis = ft_intdup(matrix[s_lis - 1], s_lis);
	free_matrix((void **)matrix, s_lis);
}
