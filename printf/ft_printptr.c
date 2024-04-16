/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:36:02 by atarsi            #+#    #+#             */
/*   Updated: 2022/02/11 19:13:14 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_h(unsigned long int nb)
{
	char				*hexa;
	unsigned long int	output;

	hexa = "0123456789abcdef";
	output = 0;
	if (nb < 0)
		nb = (4294967296 + nb);
	if (nb > 15)
		output += output + ft_putnbr_h(nb / 16);
	output += write(1, &hexa[nb % 16], 1);
	return (output);
}

int	ft_printptr(va_list arg)
{
	unsigned long	n;
	int				ptr;

	n = va_arg(arg, unsigned long);
	write (1, "0x", 2);
	ptr = ft_putnbr_h(n);
	return (ptr + 2);
}
