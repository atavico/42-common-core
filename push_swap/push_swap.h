/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 18:11:55 by atarsi            #+#    #+#             */
/*   Updated: 2022/06/13 19:42:30 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_moves
{
	int	moves;
	int	n_b;
	int	dir_b;
	int	n_a;
	int	dir_a;
	int	ind_a;
}				t_moves;

typedef struct s_a
{
	int		*a;
	int		*b;
	int		*lis;
	int		size_a;
	int		size_b;
	int		size_lis;
	t_moves	ptr;
}					t_a;

void	ft_split_str(t_a *struct_a, char *av[], int argc);
int		*ft_intdup(int *array, int size);
void	print_stack(int *a, int size);
void	swap(int *a, int *b);
void	swap_a(t_a *data);
void	swap_b(t_a *data);
void	swap_s(t_a *data);
void	push(int *ar_a, int *ar_b, int *size_a, int *size_b);
void	push_b(t_a *data);
void	push_a(t_a *data);
void	ft_search_num(t_a *data);
void	rotate(int *array, int size);
void	rot_a(t_a *data);
void	rot_b(t_a *data);
void	rot_r(t_a *data);
void	re_rotate(int *array, int size);
void	re_rot_a(t_a *data);
void	re_rot_b(t_a *data);
void	re_rot_r(t_a *data);
void	ft_algoritmo(t_a *data);
int		ft_find(int *array, int num);
int		ft_check(t_a *struct_a, char **matrix);
int		ft_atoi2(const char *str, t_a *struct_a);
int		ft_exit(char *str);
void	ft_checkdouble(t_a *struct_a, int size);
void	ft_checkdigit(t_a *struct_a, char **matrix);
void	ft_checkmalloc(void	*ptr);
int		ft_strcmp(char *s1, char *s2);
void	ft_control(t_a *data);
void	ft_correct(t_a *data, char *str);
void	ft_checkmove(char *str);
int		checker(int ac, char *av[]);
int		ft_order(int *ar, int size);
void	free_matrix(void **matrix, int size);
t_moves	ft_countmoves(t_a *data);
void	ft_lis(t_a *data);

#endif
