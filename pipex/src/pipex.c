/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:03:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/22 18:02:46 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open(int flag, char *file, t_context *p)
{
	int fd;
	
	if (flag == 'R')
		fd = open(file, O_RDONLY);
	else if (flag == 'W')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("Open failed", p);
	return (fd);
}

void	run_children(t_context *p, char **envp)
{
	p->in->pid = fork();
	if (p->in->pid == -1)
		error_exit("fork", p);
	if (p->in->pid == 0)
	{
		dup2(p->in->fd, STDIN_FILENO);
		dup2(p->write, STDOUT_FILENO);
		close(p->in->fd);
		close(p->read);
		close(p->write);
		execve(p->in->path, p->in->cmd, envp);
		error_exit("execve", p);
	}
	p->out->pid = fork();
	if (p->out->pid == -1)
		error_exit("fork", p);
	if (p->out->pid == 0)
	{
		dup2(p->read, STDIN_FILENO);
		dup2(p->out->fd, STDOUT_FILENO);
		close(p->in->fd);
		close(p->read);
		close(p->write);
		close(p->out->fd);
		execve(p->out->path, p->out->cmd, envp);
		error_exit("execve", p);
	}
}

void open_pipe(t_context *p)
{
	int fd[2];

	if (pipe(fd) == -1)
		error_exit("pipe", p);
	p->read = fd[0];
	p->write = fd[1];
}

void close_pipe(t_context *p)
{
	close(p->read);
    close(p->write);
}

int exitcode(t_context *p)
{
	int status;
	waitpid(p->in->pid, NULL, 0);
	waitpid(p->out->pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (EXIT_FAILURE);
}
