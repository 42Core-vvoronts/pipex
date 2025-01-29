/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_alfa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 17:49:08 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/19 18:10:06 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	printchar(int c, int caseflag)
{
	if (caseflag)
	{
		if (c >= 'a' && c <= 'z')
			c -= 32;
	}
	ft_putchar_fd(c, 1);
	return (1);
}

int	printstr(char *s)
{
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}
