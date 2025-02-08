/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:03:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/08 09:46:39 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	wrapped(int result, int code, t_context *p)
{
	if (result == FAIL)
		error_exit(code, p);
}

void	child_one(t_context *p, char **envp)
{
	close(p->read);
	p->in->fd = ft_open('R', p->in->file);
	wrapped(access(p->in->file, F_OK), NO_FILE, p);
	wrapped(access(p->in->file, R_OK), NO_PERM, p);
	wrapped(dup2(p->in->fd, STDIN_FILENO), STERROR, p);
	wrapped(dup2(p->write, STDOUT_FILENO), STERROR, p);
	if (p->in && p->in->fd >= 0)
	{
		wrapped(close(p->in->fd), STERROR, p);
		p->in->fd = -1;
	}
	if (p->write >= 0)
	{
		wrapped(close(p->write), STERROR, p);
		p->write = -1;
	}
	if (!p->in->cmd || !p->in->cmd[0])
		error_exit(NO_CMD, p);
	p->in->path = peek(p->paths, p->in->cmd[0]);
	if (!p->in->path)
		error_exit(EXEC, p);
	execve(p->in->path, p->in->cmd, envp);
	error_exit(EXEC, p);
}

void	child_two(t_context *p, char **envp)
{
	close(p->write);
	p->out->fd = ft_open('W', p->out->file);
	wrapped(access(p->out->file, W_OK), NO_PERM, p);
	wrapped(dup2(p->read, STDIN_FILENO), STERROR, p);
	wrapped(dup2(p->out->fd, STDOUT_FILENO), STERROR, p);
	if (p->out && p->out->fd >= 0)
	{
		wrapped(close(p->out->fd), STERROR, p);
		p->in->fd = -1;
	}
	if (p->read >= 0)
	{
		wrapped(close(p->read), STERROR, p);
		p->read = -1;
	}
	if (!p->out->cmd || !p->out->cmd[0])
		error_exit(NO_CMD, p);
	p->out->path = peek(p->paths, p->out->cmd[0]);
	if (!p->out->path)
		error_exit(EXEC, p);
	execve(p->out->path, p->out->cmd, envp);
	error_exit(EXEC, p);
}

void	run_children(t_context *p, char **envp)
{
	p->in->pid = fork();
	if (p->in->pid == 0)
		child_one(p, envp);
	else if (p->in->pid < 0)
		error_exit(STERROR, p);
	p->out->pid = fork();
	if (p->out->pid == 0)
		child_two(p, envp);
	else if (p->out->pid < 0)
		error_exit(STERROR, p);
}
