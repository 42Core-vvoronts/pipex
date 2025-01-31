/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoier.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:38:59 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:39:02 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Handles the sign of the number in the string.
 *
 * @param str The input string.
 * @param sign Pointer to an integer to store the sign.
 * @return char* The updated string pointer after handling the sign.
 */
static char	*handle_sign(char *str, int *sign)
{
	*sign = 1;
	if (*str == '+')
	{
		str++;
	}
	else if (*str == '-')
	{
		*sign = -1;
		str++;
	}
	return (str);
}

/**
 * @brief Skips any leading whitespace characters in the string.
 *
 * @param str The input string.
 * @return char* The updated string pointer after skipping whitespace.
 */
static char	*skip_whitespace(char *str)
{
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	return (str);
}

/**
 * @brief Converts a string to a long long integer with error handling.
 *
 * @param str The input string.
 * @param error Pointer to an integer to store error codes.
 * @return long long The converted long long integer.
 */
long long	ft_atoier(char *str, int *error)
{
	long long	result;
	int			sign;
	char		*mem;

	result = 0;
	str = skip_whitespace(str);
	str = handle_sign(str, &sign);
	mem = str;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			result = result * 10 + (*str++ - '0');
		else
			return (*error = nonnumer, 0);
	}
	result *= sign;
	if (str == mem)
		*error = empty;
	else if (result > INT_MAX || result < INT_MIN)
		*error = intovfl;
	else
		*error = noerror;
	return (result);
}
