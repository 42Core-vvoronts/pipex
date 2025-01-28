/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 13:52:09 by vvoronts         ###   ########.fr       */
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
		else
		{
			if (WIFEXITED(status))
				perror_message(WEXITSTATUS(status));
		}
	}
	if (exitcode == EXEC)
		exitcode = 127;
	return (exitcode);
}

void	perror_message(t_errno err)
{
	if (err == EXEC)
		perror("Error: command failed");
	else if (err == ARGS)
		ft_putendl_fd("Usage: ./pipex <in> <cmd1> <cmd2> <out>\n", STDERR);
	else if (err == NO_CMD)
		ft_putendl_fd("Error: invalid command", STDERR);
	else if (err == NO_FILE)
		ft_putendl_fd("Error: invalid filename", STDERR);
	else
		perror("Error");
}

void	error_exit(t_errno err, t_context *p)
{
	int	exitcode;

	if (err == EXEC)
		exitcode = 127;
	else
		exitcode = 1;
	perror_message(err);
	if (p)
	{
		close_pipe(p);
		cleanup(p);
	}
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
