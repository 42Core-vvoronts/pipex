/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 11:52:56 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	wait_processes(t_context *p)
{
	pid_t	pid;
	int		status;
	int		exitcode;

	pid = 0;
	status = 0;
	exitcode = 1;
	while (pid != -1)
	{
		pid = wait(&status);
		if (pid == p->out->pid && WIFEXITED(status))
			exitcode = WEXITSTATUS(status);
	}
	return (exitcode);
}

void	perror_message(t_errno err)
{
	if (err == EXEC)
		perror("Error: command failed");
	else if (err == ARGS)
		perror("Error. Usage: ./pipex <in> <cmd1> <cmd2> <out>\n");
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
}

void	error_exit(t_errno err, t_context *p)
{
	int	exitcode;

	if (err == EXEC)
		exitcode = 127;
	else
		exitcode = 1;
	perror_message(err);
	close_pipe(p);
	cleanup(p);
	exit(exitcode);
}

void	validate_args(int argc, char **argv)
{
	if (argc != 5)
		error_exit(ARGS, NULL);
	if (!argv[2][0] || !argv[3][0])
		error_exit(NO_CMD, NULL);
	if (!argv[1][0] || !argv[4][0])
		error_exit(NO_FILE, NULL);
}
