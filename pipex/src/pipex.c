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
		error_exit(OPEN, p);
	return (fd);
}

void child_one(t_context *p, char **envp)
{
	close(p->read);
	dup2(p->in->fd, STDIN_FILENO);
	dup2(p->write, STDOUT_FILENO);
	close(p->in->fd);
	close(p->write);

	p->in->path = peek(p->paths, p->in->cmd[0], p);
	execve(p->in->path, p->in->cmd, envp);
	error_exit(EXEC, p);
}

void	child_two(t_context *p, char **envp)
{
	close(p->write);
	dup2(p->read, STDIN_FILENO);
	dup2(p->out->fd, STDOUT_FILENO);
	close(p->out->fd);
	close(p->read);
	
	p->out->path = peek(p->paths, p->out->cmd[0], p);
	execve(p->out->path, p->out->cmd, envp);
	error_exit(EXEC, p);
}

void	run_children(t_context *p, char **envp)
{
	p->in->pid = fork();
	if (p->in->pid == 0)
		child_one(p, envp);
	else if (p->in->pid < 0)
		error_exit(FORK, p);

	p->out->pid = fork();
	if (p->out->pid == 0)
		child_two(p, envp);
	else if (p->out->pid < 0)
		error_exit(FORK, p);
	
}

void	open_pipe(t_context *p)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_exit(PIPE, p);
	p->read = fd[0];
	p->write = fd[1];
}

void	close_pipe(t_context *p)
{
	close(p->read);
    close(p->write);
}
