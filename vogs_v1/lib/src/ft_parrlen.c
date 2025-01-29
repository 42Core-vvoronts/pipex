/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:39:55 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:39:58 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

/**
 * @brief Calculates the length of a NULL-terminated array of pointers.
 * 
 * @param arr The NULL-terminated array of pointers.
 * @return The number of elements in the array, excluding the NULL terminator.
 */
size_t	ft_parrlen(void *arr)
{
	void	**mem;
	void	**arr2;

	if (!arr)
		return (0);
	arr2 = (void **)arr;
	mem = arr2;
	while (*arr2)
		arr2++;
	return (arr2 - mem);
}
