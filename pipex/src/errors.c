/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/26 18:13:33 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int valid_args(int argc, char **argv)
{
	if (argc != 5)
		return(0);
	if (argv[2][0] == '\0' || argv[3][0] == '\0')
	{
		if (argv[2][0] == '\0')
			ft_putstr_fd("Error: Command not found\n", 2);
		if (argv[3][0] == '\0')
			ft_putstr_fd("Error: Command not found\n", 2);
		return (0);
	}
	return (1);
}

void	handle_error(int errno, t_pipe *pip)
{
	if (errno == SUCCESS)
		return;
	else if (errno == SYNTAX_FAIL)
		perror("Error: wrong syntax\nUsage: ./pip file1 cmd1 cmd2 file2\n");
	else if (errno == CMD_FAIL)
	{
		perror("Error: Command not found\n");
		cleanup(pip);
		exit(127);
	}
	else if (errno == EXEC_FAIL)
		perror("Error: Problem with execution\n");
	else if (errno == MALLOC_FAIL)
		perror("Error: Memory allocation failed\n");
	else if (errno == OPEN_FAIL)
		perror("Error: File opening failed\n");
	else if (errno == PIPE_FAIL)
		perror("Error: Pipe failed\n");
	else
		perror("Error: Unknown error\n");
	cleanup(pip);
	exit(1);
}

void	cleanup(t_pipe *pip)
{
	close(pip->infile->fd);
	close(pip->outfile->fd);
	if (pip)
	{
		free(pip->infile->cmd);
		free(pip->outfile->cmd);
		free(pip->infile);
		free(pip->outfile);
		free(pip->paths);
		free(pip);
	}
}