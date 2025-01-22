/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:27:56 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/20 09:51:38 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printarg(const char *specifyer, va_list ap)
{
	if (*specifyer == 'c')
		return (printchar(va_arg(ap, int), 0));
	else if (*specifyer == '%')
		return (printchar('%', 0));
	else if (*specifyer == 's')
		return (printstr(va_arg(ap, char *)));
	else if (*specifyer == 'p')
		return (printptr(va_arg(ap, void *), 0));
	else if (*specifyer == 'd' || *specifyer == 'i')
		return (printint(va_arg(ap, int)));
	else if (*specifyer == 'x')
		return (printnum(va_arg(ap, unsigned int), 16, 0));
	else if (*specifyer == 'X')
		return (printnum(va_arg(ap, unsigned int), 16, 1));
	else if (*specifyer == 'u')
		return (printnum(va_arg(ap, unsigned int), 10, 0));
	return (0);
}

int	printall(const char *s, va_list args)
{
	int		counter;

	counter = 0;
	while (*s)
	{
		if (*s != '%')
		{
			ft_putchar_fd(*s, 1);
			counter += 1;
		}
		else
			counter += printarg(++s, args);
		s++;
	}
	return (counter);
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		printed;

	va_start(args, string);
	printed = printall(string, args);
	va_end(args);
	return (printed);
}
