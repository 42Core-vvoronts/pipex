/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 09:36:10 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 15:00:33 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*getenv_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char	*peek(char **paths, char *cmd)
{
	char	*temp;
	char	*path;

	if (ft_strchr(cmd, '/'))
	{
		path = ft_strdup(cmd);
		if (!path)
			exit(MALLOC);
		return (path);
	}
	while (*paths)
	{
		temp = ft_strjoin(*paths, "/");
		if (!temp)
			exit(MALLOC);
		path = ft_strjoin(temp, cmd);
		if (!path)
			exit(MALLOC);
		free(temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		paths++;
	}
	return (NULL);
}
