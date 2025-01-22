/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parrclean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 10:39:42 by vvoronts          #+#    #+#             */
/*   Updated: 2024/12/08 10:39:45 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "elibft.h"

long long	ft_parrclean(int code, void (*del)(void *), void *arr1, void *arr2)
{
	void	**a1;
	void	**a2;

	a1 = (void **)arr1;
	while (arr1 && *a1)
		del(*a1++);
	free(arr1);
	a2 = (void **)arr2;
	while (arr2 && *a2)
		del(*a2++);
	free(arr2);
	return ((long long)code);
}
