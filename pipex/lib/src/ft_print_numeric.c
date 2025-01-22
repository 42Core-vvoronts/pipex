/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numeric.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:49:27 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/22 10:24:39 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n == 2147483647)
		return (10);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	printnum(size_t n, int base, int caseflag)
{
	char			*symbol;
	size_t			sbase;
	unsigned int	printed;

	symbol = "0123456789abcdef";
	sbase = (size_t)base;
	printed = 0;
	if (n < sbase)
	{
		printed += printchar(symbol[n], caseflag);
		return (printed);
	}
	printed += printnum(n / sbase, base, caseflag);
	printed += printnum(n % sbase, base, caseflag);
	return (printed);
}

int	printint(int n)
{
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", 1);
		return (11);
	}
	ft_putnbr_fd(n, 1);
	return (ft_numlen(n));
}

int	printptr(void *ptr, int caseflag)
{
	int		printed;

	if (ptr == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	printed = 0;
	printed += printstr("0x");
	printed += printnum((size_t)ptr, 16, caseflag);
	return (printed);
}
