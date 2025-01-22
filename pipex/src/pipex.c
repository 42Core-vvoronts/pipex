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
#include <fcntl.h>
#include <unistd.h> 
#include <sys/wait.h>


// open: Open files (infile and outfile).
// pipe: Create a pipe to connect cmd1 and cmd2.
// fork: Create two child processes.
// dup2: Redirect file descriptors between the processes.
// execve: Run the commands in the children.
// waitpid: Wait for child processes to finish.

// ./pip infile cmd1 cmd2 outfile

typedef struct s_cmd
{
	int 	pid;
	char	**cmd;
	char	*name;
	int		fd;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd 		*infile; //left
	t_cmd 		*outfile; //right
	int 		newfd[2];
	char		**paths;
	
} t_pipe;


int	ft_open(int flag, char *file)
{
	int fd;
	
	if (flag == 'R')
		fd = open(file, O_RDONLY);
	else if (flag == 'W')
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printf("Error fd\n");
		exit(1);
	}
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
		{
            printf("Error: Memory allocation failed\n");
			exit(1);
		}
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

int	invalid_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_printf("Usage: ./pip file1 cmd1 cmd2 file2\n");
		return (1);
	}
	else if (!argv[1][0] || !argv[4][0])
	{
		ft_printf("Error: infile or outfile is empty\n");
		return (1);
	}

	else if (!argv[2][0] || !argv[3][0])
	{
		ft_printf("Error: cmd1 or cmd2 is empty\n");
		return (1);
	}
	return (0);
}

t_pipe *init_structs(char **argv, char **envp)
{
	t_pipe *pip;

	pip = (t_pipe *)malloc(sizeof(t_pipe));

	pip->infile = (t_cmd *)malloc(sizeof(t_cmd));
	pip->outfile = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pip->infile || !pip->outfile)
	{
		ft_printf("Memory allocation failed\n");
	}
	
	pip->infile->fd = ft_open('R', argv[1]);
	pip->infile->name = argv[1];
	pip->outfile->fd = ft_open('W', argv[4]);
	pip->outfile->name = argv[4];

	pip->infile->cmd = ft_split(argv[2], ' ');
	pip->outfile->cmd = ft_split(argv[3], ' ');
	pip->paths = ft_split(getenv_paths(envp), ':');
	
	ft_printf("< %s %s | %s > %s\n", pip->infile->name, pip->infile->cmd[0], pip->outfile->cmd[0], pip->outfile->name);
	return (pip);
}


void	connect_files(t_pipe *pip)
{
	if (pipe(pip->newfd) < 0)
		ft_printf("Error pipe\n");
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
			perror("Error executing cmd1");
		}
		else
			printf("Error: command not found\n");
		exit(1);
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
			perror("Error executing cmd2");
		}
		else
		{
			printf("Error: command not found\n");
		}
		exit(1);
	}

}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	*pip;

	if (invalid_args(argc, argv))
		return (1);

	pip = init_structs(argv, envp);
	connect_files(pip);
	// child for cmd1
	fork_first_child(pip, envp);
	// child for cmd2
	fork_second_child(pip, envp);

	close(pip->newfd[0]);
	close(pip->newfd[1]);

	// close(pip->infile->fd);
	// close(pip->outfile->fd);

	// Wait for children to finish
	waitpid(pip->infile->pid, NULL, 0);
	waitpid(pip->outfile->pid, NULL, 0);


	
	return (0);
}
