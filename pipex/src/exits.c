/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/27 19:38:42 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_processes(t_context *p)
{
	int status;
	int exitcode;
	
	status = 0;
	exitcode = 1;
	close(p->in->fd);
    close(p->out->fd);
    close(p->read);
    close(p->write);
	
	waitpid(p->in->pid, NULL, 0);
	waitpid(p->out->pid, &status, 0);
	if (WIFEXITED(status))
		exitcode = WEXITSTATUS(status);
	return (exitcode);
}

void	error_exit(t_errno err, t_context *p) 
{
	if (err == EXEC)
	{
		perror("Error: command failed");
		cleanup(p);
		exit(127);
	}
	else if (err == ARGS)
		perror("Error: invalid arguments. Usage: ./pipex <in> <cmd1> <cmd2> <out>\n");
	else if (err == NO_CMD)
		perror("Error: invalid command");
	else if (err == NO_FILE)
		perror("Error: invalid filename");
	else if (err == OPEN)
		perror("Error: can't open file");
	else if (err == PIPE)
		perror("Error: pipe() failed");
	else if (err == FORK)
		perror("Error: fork() failed");
	else if (err == DUP)
		perror("Error: dup2() failed");
	else if (err == FILE_FAIL)
		perror("Error: file doesn't exist or has no access");
	else if (err == PATH)
		perror("Error: path not found");
	else if (err == MALLOC)
		perror("Error: memory allocation failed");
	cleanup(p);
	exit(EXIT_FAILURE);
}

void	validate_args(int argc, char **argv)
{
	if (argc != 5)
		error_exit(ARGS, NULL);
	if (!argv[2][0]|| !argv[3][0])
		error_exit(NO_CMD, NULL);
	if (!argv[1][0]|| !argv[4][0])
		error_exit(NO_FILE, NULL);
}
