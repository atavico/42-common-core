/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 16:03:00 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/11 19:21:14 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_checkmove(char *str)
{
	if (ft_strcmp(str, "pa\n") == 0)
		return ;
	if (ft_strcmp(str, "pb\n") == 0)
		return ;
	if (ft_strcmp(str, "ra\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		return ;
	if (ft_strcmp(str, "rb\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		return ;
	if (ft_strcmp(str, "rra\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		return ;
	if (ft_strcmp(str, "rrb\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		return ;
	if (ft_strcmp(str, "sa\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		return ;
	if (ft_strcmp(str, "sb\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		return ;
	ft_exit("error\n");
}

void	ft_correct(t_a *data, char *str)
{
	ft_checkmove(str);
	if (ft_strcmp(str, "pa\n") == 0)
		push(data->b, data->a, &data->size_b, &data->size_a);
	if (ft_strcmp(str, "pb\n") == 0)
		push(data->a, data->b, &data->size_a, &data->size_b);
	if (ft_strcmp(str, "ra\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		rotate(data->a, data->size_a);
	if (ft_strcmp(str, "rb\n") == 0 || ft_strcmp(str, "rr\n") == 0)
		rotate(data->b, data->size_b);
	if (ft_strcmp(str, "rra\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		re_rotate(data->a, data->size_a);
	if (ft_strcmp(str, "rrb\n") == 0 || ft_strcmp(str, "rrr\n") == 0)
		re_rotate(data->b, data->size_b);
	if (ft_strcmp(str, "sa\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		swap(&data->a[0], &data->a[1]);
	if (ft_strcmp(str, "sb\n") == 0 || ft_strcmp(str, "ss\n") == 0)
		swap(&data->b[0], &data->b[1]);
}

void	ft_control(t_a *data)
{
	char	*str;

	str = get_next_line(0);
	while (1)
	{
		if (str == NULL)
			break ;
		ft_correct(data, str);
		free (str);
		str = get_next_line(0);
	}
	if (str != NULL)
		free(str);
	if (ft_order(data->a, data->size_a) == 1)
		ft_putstr_fd("OK\n", 1);
	else
		ft_putstr_fd("KO\n", 1);
}

int	main(int ac, char *av[])
{
	t_a	data;

	if (ac <= 1)
		return (0);
	else
	{
		ft_split_str(&data, av, ac);
		ft_control (&data);
	}
	free (data.a);
	free (data.b);
	return (0);
}
