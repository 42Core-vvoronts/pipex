/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 17:38:30 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/05 17:38:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	handle(int error)
{
	if (error == AC_ERR)
		perror("Not enough arguments\n");
	if (error == FILE1_ERR)
		perror("Invalid input file\n");
	if (error == FILE2_ERR)
		perror("Invalid output file\n");
	if (error == PIPE_ERR)
		perror("Error calling pipe\n");
	if (error == FORK_ERR)
		perror("Error calling fork\n");
	if (error == DUP_ERR)
		perror("Error calling dup\n");
	if (error == MALLOC_ERR)
		perror("Error calling malloc\n");
	exit(error);
}