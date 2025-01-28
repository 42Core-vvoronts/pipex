/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:36:00 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 14:06:45 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_structs(t_context **p, char **argv, char **envp)
{
	*p = (t_context *)malloc(sizeof(t_context));
	if (!p)
		error_exit(MALLOC, *p);
	(*p)->in = (t_cmd *)malloc(sizeof(t_cmd));
	(*p)->out = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(*p)->in || !(*p)->out)
		error_exit(MALLOC, *p);
	(*p)->in->fd = -1;
	(*p)->in->file = argv[1];
	(*p)->out->fd = -1;
	(*p)->out->file = argv[4];
	(*p)->in->cmd = ft_split(argv[2], ' ');
	(*p)->out->cmd = ft_split(argv[3], ' ');
	(*p)->paths = ft_split(getenv_paths(envp), ':');
	(*p)->in->path = NULL;
	(*p)->out->path = NULL;
	(*p)->read = 0;
	(*p)->write = 0;
}

void	clean_array(char **array)
{
	char	**tmp;

	if (array)
	{
		tmp = array;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(array);
	}
}

void	cleanup(t_context *p)
{
	if (p)
	{
		if (p->in)
		{
			clean_array(p->in->cmd);
			if (p->in->path)
				free(p->in->path);
			free(p->in);
		}
		if (p->out)
		{
			clean_array(p->out->cmd);
			if (p->out->path)
				free(p->out->path);
			free(p->out);
		}
		if (p->paths)
		{
			clean_array(p->paths);
		}
		free(p);
	}
	p = NULL;
}
