/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:40:03 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:40:05 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Compares two null-terminated strings lexicographically.
 *
 * @param s1 The first string to be compared.
 * @param s2 The second string to be compared.
 * @return int Returns an integer less than, equal to, or greater than zero
 *         if s1 is found, respectively, to be less than, to match, or be
 *         greater than s2.
 */
int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		else if ((unsigned char)*s1 < (unsigned char)*s2)
			return (-1);
		s1++;
		s2++;
	}
	return (0);
}
