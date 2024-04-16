/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 19:03:51 by atarsi            #+#    #+#             */
/*   Updated: 2022/02/10 19:04:09 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	argtoexe(va_list arg, char c)
{
	int	out;

	out = 0;
	if (c == 'c')
		out = ft_printchar(arg);
	else if (c == 's')
		out = ft_printstring(arg);
	else if (c == 'p')
		out = ft_printptr(arg);
	else if (c == 'd' || c == 'i')
		out = ft_printinteger(arg);
	else if (c == 'u')
		out = ft_printunsint(arg);
	else if (c == 'x')
		out = ft_printhexalower(arg);
	else if (c == 'X')
		out = ft_printhexaupper(arg);
	else if (c == '%')
		out = ft_printpercent(c);
	else
		return (0);
	return (out);
}

int	ft_printf(const char *string, ...)
{
	va_list	arg;
	int		i;
	int		out;

	i = 0;
	out = 0;
	va_start(arg, string);
	while (string[i])
	{
		if (string[i] != '%')
			out += ft_putchar(string[i]);
		else
		{
			out += argtoexe(arg, string[i + 1]);
			i++;
		}
		i++;
	}
	va_end(arg);
	return (out);
}
