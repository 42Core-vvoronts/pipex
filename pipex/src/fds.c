/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:46:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 13:20:18 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	close(p->in->fd);
	close(p->out->fd);
	close(p->read);
	close(p->write);
}

int	ft_open(int flag, char *file, t_context *p)
{
	int	fd;

	if (flag == 'R')
		fd = open(file, O_RDONLY);
	else if (flag == 'W')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = -1;
	if (fd < 0)
		error_exit(OPEN, p);
	return (fd);
}
