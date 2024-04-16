/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 18:01:54 by atarsi            #+#    #+#             */
/*   Updated: 2022/02/11 19:11:44 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

int		ft_printf(const char *param, ...);
int		ft_printchar(va_list arg);
int		ft_printstring(va_list arg);
int		ft_printhexaupper(va_list arg);
int		ft_putnbr_hexalower(unsigned int nb);
int		ft_putnbr_hexaupper(unsigned int nb);
int		ft_printhexalower(va_list arg);
int		ft_printinteger(va_list arg);
int		ft_printpercent(char c);
int		ft_printptr(va_list arg);
int		ft_printunsint(va_list arg);
int		ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);
size_t	ft_strlen(const char *s);

#endif
