/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:36:00 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/27 11:40:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_structs(t_context **p, char **argv, char **envp)
{
	*p = (t_context *)malloc(sizeof(t_context)); // MALLOC
	if (!p)
		error_exit("Malloc", *p);

	(*p)->in = (t_cmd *)malloc(sizeof(t_cmd)); // MALLOC
	(*p)->out = (t_cmd *)malloc(sizeof(t_cmd)); // MALLOC
	if (!(*p)->in || !(*p)->out)
		error_exit("Malloc", *p);
	(*p)->in->fd = ft_open('R', argv[1], *p);
	(*p)->in->file = argv[1];
	(*p)->out->fd = ft_open('W', argv[4], *p);
	(*p)->out->file = argv[4];
	(*p)->in->cmd = ft_split(argv[2], ' '); // MALLOC
	(*p)->out->cmd = ft_split(argv[3], ' '); // MALLOC
	(*p)->paths = ft_split(getenv_paths(envp, *p), ':'); // MALLOC
	(*p)->in->path = peek((*p)->paths, (*p)->in->cmd[0], *p);
	(*p)->out->path = peek((*p)->paths, (*p)->out->cmd[0], *p);
	(*p)->read = 0;
	(*p)->write = 0;
}

void clean_array(char **array)
{
    if (array)
    {
        char **tmp = array;
        while (*tmp)
        {
            free(*tmp);
            tmp++;
        }
        free(array);
    }
}

void cleanup(t_context *p)
{
    if (p)
    {
        if (p->in)
        {
            clean_array(p->in->cmd);
            free(p->in);
        }

        if (p->out)
        {
            clean_array(p->out->cmd);
            free(p->out);
        }

        if (p->paths)
        {
            clean_array(p->paths);
        }

        free(p);
    }
}

