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

void wrapper(int result, t_context *p)
{
	if (result == FAIL)
		error_exit(STERROR, p);
}

void	child_one(t_context *p, char **envp)
{
	close(p->read);
	p->in->fd = ft_open('R', p->in->file);
	if ((p->in->fd == FAIL))
	{
		if (access(p->in->file, F_OK) == FAIL)
			error_exit(NO_FILE, p);
		if (access(p->in->file, R_OK) == FAIL)
			error_exit(NO_PERM, p);
	}
	dup2(p->in->fd, STDIN_FILENO);
	dup2(p->write, STDOUT_FILENO);
	close(p->in->fd);
	close(p->write);
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
	if ((p->out->fd == FAIL))
	{
		if (access(p->out->file, W_OK) == FAIL)
			error_exit(NO_PERM, p);		
	}
	dup2(p->read, STDIN_FILENO);
	dup2(p->out->fd, STDOUT_FILENO);
	close(p->out->fd);
	close(p->read);
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
