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

// open: Open files (infile and outfile).
// pipe: Create a pipe to connect cmd1 and cmd2.
// fork: Create two child processes.
// dup2: Redirect file descriptors between the processes.
// execve: Run the commands in the children.
// waitpid: Wait for child processes to finish.

// ./pip infile cmd1 cmd2 outfile

int	ft_open(int flag, char *file)
{
	int fd;
	
	if (flag == 'R')
		fd = open(file, O_RDONLY);
	else if (flag == 'W')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		handle_error(OPEN_FAIL, NULL);
	return (fd);
}

char	*getenv_paths(char **envp)
{
	int i;
	
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *peek(char **paths, char *cmd)
{
    char *temp;
    char *command;
    int i = 0;

    if (ft_strchr(cmd, '/'))
    {
        command = ft_strdup(cmd);
        if (!command)
			handle_error(MALLOC_FAIL, NULL);
        return (command);
    }

    while (paths[i])
    {
        temp = ft_strjoin(paths[i], "/");
        command = ft_strjoin(temp, cmd);
        free(temp);
        if (access(command, F_OK) == 0)
            return (command);

        free(command);
        i++;
    }

    return (NULL);
}



t_pipe *init_structs(char **argv, char **envp)
{
	t_pipe *pip;

	pip = (t_pipe *)malloc(sizeof(t_pipe));

	pip->infile = (t_cmd *)malloc(sizeof(t_cmd));
	pip->outfile = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pip->infile || !pip->outfile)

	
	pip->infile->fd = ft_open('R', argv[1]);
	pip->infile->name = argv[1];
	pip->outfile->fd = ft_open('W', argv[4]);
	pip->outfile->name = argv[4];

	pip->infile->cmd = ft_split(argv[2], ' ');
	pip->outfile->cmd = ft_split(argv[3], ' ');
	pip->paths = ft_split(getenv_paths(envp), ':');
	
	// perror("< %s %s | %s > %s\n", pip->infile->name, pip->infile->cmd[0], pip->outfile->cmd[0], pip->outfile->name);
	return (pip);
}


void	connect_files(t_pipe *pip)
{
	if (pipe(pip->newfd) < 0)
		handle_error(PIPE_FAIL, pip);
}

void fork_first_child(t_pipe *pip, char **envp)
{
	pip->infile->pid = fork();
	if (pip->infile->pid == 0)
	{
        dup2(pip->infile->fd, 0);
        dup2(pip->newfd[1], 1);
        close(pip->newfd[0]);

		char *path = peek(pip->paths, pip->infile->cmd[0]);
		if (path)
		{
			execve(path, pip->infile->cmd, envp);
			handle_error(EXEC_FAIL, pip);
		}
		else
			handle_error(CMD_FAIL, pip);
	}

}

void	fork_second_child(t_pipe *pip, char **envp)
{
	pip->outfile->pid = fork();
	if (pip->outfile->pid == 0)
	{
        dup2(pip->newfd[0], 0);
        dup2(pip->outfile->fd, 1);
        close(pip->newfd[1]);

		char *path = peek(pip->paths, pip->outfile->cmd[0]);
		if (path)
		{
			execve(path, pip->outfile->cmd, envp);
			handle_error(EXEC_FAIL, pip);
		}
		else
			handle_error(CMD_FAIL, pip);
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pip;

	if (valid_args(argc, argv))
	{
		pip = init_structs(argv, envp);

		connect_files(pip);
		fork_first_child(pip, envp);
		fork_second_child(pip, envp);

		close(pip->newfd[0]);
		close(pip->newfd[1]);

		// Wait for children to finish
		waitpid(pip->infile->pid, NULL, 0);
		waitpid(pip->outfile->pid, NULL, 0);
		return (0);
	}
	else
		return (0);
}
