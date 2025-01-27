/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/27 11:04:23 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void error_exit(char *message, t_context *p) 
{
	perror(message);
	// if (message == "Command not found")
	// 	exit(EXIT_CMD);
	cleanup(p);
	exit(EXIT_FAILURE);
}

void validate_args(int argc, char **argv)
{
	if (argc != 5)
		error_exit("Usage: ./pipex <in> <cmd1> <cmd2> <out>\n", NULL);
	if (!argv[2][0]|| !argv[3][0])
		error_exit("No command", NULL);
	if (!argv[1][0]|| !argv[4][0])
		error_exit("No filename", NULL);
}
