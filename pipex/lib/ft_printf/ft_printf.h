/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 19:28:06 by vvoronts          #+#    #+#             */
/*   Updated: 2024/09/19 17:53:21 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

int	ft_printf(const char *str, ...);
int	printall(const char *s, va_list args);
int	printarg(const char *specifyer, va_list ap);
int	printchar(int c, int caseflag);
int	printstr(char *s);
int	ft_numlen(int n);
int	printnum(size_t n, int base, int caseflag);
int	printint(int n);
int	printptr(void *ptr, int caseflag);

#endif
