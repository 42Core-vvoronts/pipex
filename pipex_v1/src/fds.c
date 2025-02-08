/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:46:09 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/08 09:37:32 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	open_pipe(t_context *p)
{
	int	fd[2];

	wrapped(pipe(fd), STERROR, p);
	p->read = fd[0];
	p->write = fd[1];
}

void	close_pipe(t_context *p)
{
	if (p)
	{
		if (p->read >= 0)
		{
			close(p->read);
			p->read = -1;
		}
		if (p->write >= 0)
		{
			close(p->write);
			p->write = -1;
		}
	}
}

int	ft_open(int flag, char *file)
{
	int	fd;

	if (flag == 'R')
		fd = open(file, O_RDONLY);
	else if (flag == 'W')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		fd = -1;
	return (fd);
}
