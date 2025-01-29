/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 18:02:23 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/29 12:00:58 by vvoronts         ###   ########.fr       */
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
	if (exitcode == EXEC || exitcode == NO_CMD)
		exitcode = EXECUTE;
	if (exitcode != SUCCESS)
		exitcode = ERROR;
	return (exitcode);
}

void	perror_message(t_errno err)
{
	if (err == NO_CMD || err == EXEC)
		ft_putendl_fd("pipex: command not found", STDERR_FILENO);
	else if (err == ARGS)
		ft_putendl_fd("pipex: : syntax error", STDERR_FILENO);
	else if (err == NO_FILE)
		ft_putendl_fd("pipex: : no such file or directory", STDERR_FILENO);
	else if (errno != NOER)
	{
		perror("pipex: ");
	}
}

void	error_exit(t_errno err, t_context *p)
{
	int	exitcode;

	perror_message(err);
	if (err == EXEC || err == NO_CMD)
		exitcode = EXECUTE;
	else
		exitcode = ERROR;
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
	if (!argv[1][0] && !argv[4][0])
	{
		perror_message(NO_FILE);
		error_exit(NO_FILE, NULL);
	}
	if (!argv[1][0] || !argv[4][0])
		error_exit(NO_FILE, NULL);
	if (!argv[2][0] && !argv[3][0])
	{
		perror_message(NO_CMD);
		error_exit(NO_CMD, NULL);
	}
	if (!argv[2][0] || !argv[3][0])
		error_exit(NO_CMD, NULL);
}
