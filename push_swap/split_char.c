/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 18:23:47 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/11 19:33:27 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_create_array(t_a *struct_a, char **matrix)
{
	int	i;

	struct_a->size_b = 0;
	struct_a->a = malloc (sizeof(int) * struct_a->size_a);
	struct_a->b = malloc (sizeof(int) * struct_a->size_a);
	i = 0;
	while (i < struct_a->size_a)
	{
		struct_a->a[i] = ft_atoi2(matrix[i], struct_a);
		i++;
	}
}

void	ft_split_str(t_a *struct_a, char *av[], int ac)
{
	char	**matrix;

	struct_a->size_a = 0;
	if (ac == 2)
	{
		matrix = ft_split (av[1], ' ');
		while (matrix[struct_a->size_a] != NULL)
			struct_a->size_a++;
	}
	else
	{
		matrix = &av[1];
		struct_a->size_a = ac - 1;
	}
	ft_checkdigit(struct_a, matrix);
	ft_create_array(struct_a, matrix);
	if (ac == 2)
		free_matrix((void **)matrix, struct_a->size_a);
	ft_checkdouble (struct_a, struct_a->size_a);
}
