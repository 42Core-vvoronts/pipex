/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:36:10 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/27 11:53:06 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getenv_paths(char **envp, t_context *p)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	error_exit("No PATH in env", p);
	return (NULL);
}

char *peek(char **paths, char *cmd, t_context *p)
{
    char *temp;
    char *path;
    int i = 0;

    if (ft_strchr(cmd, '/'))
    {
        path = ft_strdup(cmd);
        if (!path)
			error_exit("Malloc", p);
        return (path);
    }

    while (paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        path = ft_strjoin(temp, cmd);
        free(temp);
        if (access(path, F_OK) == 0)
            return (path);

        free(path);
        i++;
    }
    return (error_exit("Command not found", p), NULL);
}