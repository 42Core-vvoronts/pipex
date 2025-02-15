/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/29 17:21:10 by vvoronts         ###   ########.fr       */
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
		{
			exitcode = WEXITSTATUS(status);
			perror_message(exitcode);
		}
		else if (pid == p->in->pid)
			perror_message(WEXITSTATUS(status));
	}
	return (exitcode);
}

void	perror_message(int err)
{
	if (err == NO_CMD || err == EXEC)
		ft_putendl_fd("pipex: command not found", STDERR_FILENO);
	else if (err == NO_FILE)
		ft_putendl_fd("pipex: no such file or directory", STDERR_FILENO);
	else if (err == ARGS)
		ft_putendl_fd("pipex: syntax error", STDERR_FILENO);
	else if (errno != SUCCESS)
	{
		perror("pipex");
	}
}

void	error_exit(int err, t_context *p)
{
	close_pipe(p);
	cleanup(p);
	exit(err);
}

void	validate_args(int argc, char **argv)
{
	if (argc != 5)
	{
		perror_message(ARGS);
		exit(STERROR);
	}
	if (!argv[1][0] || !argv[4][0])
	{
		if (!argv[1][0])
			perror_message(NO_FILE);
		if (!argv[4][0])
			perror_message(NO_FILE);
		exit(STERROR);
	}
	if (!argv[2][0] || !argv[3][0])
	{
		if (!argv[2][0])
			perror_message(NO_CMD);
		if (!argv[3][0])
			perror_message(NO_CMD);
		exit(STERROR);
	}
}
