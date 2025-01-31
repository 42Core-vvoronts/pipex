/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoiner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:40:10 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:40:12 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Joins two strings into a new string.
 *
 * This function allocates memory and concatenates the strings s1 and s2.
 * The caller is responsible for freeing the allocated memory.
 * Protects ft_strlener(NULL) from segfault.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return A pointer to the newly allocated string, or NULL if allocation fails.
 */
char	*ft_strjoiner(char const *s1, char const *s2)
{
	size_t	len;
	char	*result;
	char	*mem;

	len = ft_strlener(s1) + ft_strlener(s2);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	mem = result;
	while (*s1)
		*result++ = *s1++;
	while (*s2)
		*result++ = *s2++;
	*result = '\0';
	return (mem);
}
