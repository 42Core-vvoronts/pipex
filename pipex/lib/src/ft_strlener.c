/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:40:17 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:40:20 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Computes the length of the string.
 *
 * This function takes a constant character pointer as input and returns the 
 * length of the string. If the input string is NULL, it returns 0.
 *
 * @param str The input string whose length is to be computed.
 * @return The length of the input string, or 0 if the input string is NULL.
 */
size_t	ft_strlener(const char *str)
{
	const char	*mem;

	if (!str)
		return (0);
	mem = str;
	while (*str)
		str++;
	return (str - mem);
}
