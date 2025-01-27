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


void check_args(int argc, char **argv)
{
	if (argc != 5)
        error_exit("Usage: ./pipex <in> <cmd1> <cmd2> <out>\n");
	if (!argv[2][0]|| !argv[3][0])
		error_exit("Usage: ./pipex <in> <cmd1> <cmd2> <out>\n");
	if (!argv[1][0] || !argv[4][0])		
        error_exit("Usage: ./pipex <in> <cmd1> <cmd2> <out>\n");

}

void error_exit(char *message) 
{
    perror(message);
	// if (message == "Command not found")
	// 	exit(EXIT_CMD);
    exit(EXIT_FAILURE);
}

// void	handle_error(enum e_errno type, t_pipe *pip)
// {
// 	if (type == SUCCESS)
// 		return;
// 	else if (type == SYNTAX_FAIL)
// 		perror("Error: wrong syntax\nUsage: ./pip file1 cmd1 cmd2 file2\n");
// 	else if (type == CMD_FAIL)
// 	{
// 		perror("Error: Command not found\n");
// 		cleanup(pip);
// 		exit(127);
// 	}
// 	else if (type == EXEC_FAIL)
// 		perror("Error: Problem with execution\n");
// 	else if (type == MALLOC_FAIL)
// 		perror("Error: Memory allocation failed\n");
// 	else if (type == OPEN_FAIL)
// 		perror("Error: File opening failed\n");
// 	else if (type == PIPE_FAIL)
// 		perror("Error: Pipe failed\n");
// 	else if (type == FORK_FAIL)
// 		perror("Error: Fork failed\n");
// 	else
// 		perror("Error: Unknown error\n");
// 	cleanup(pip);
// 	exit(1);
// }

void	cleanup(t_pipe *pip)
{
	close(pip->infile->fd);
	close(pip->outfile->fd);
	if (pip)
	{
		if (pip->infile && pip->infile->cmd)
			free(pip->infile->cmd);
		if (pip->outfile)
			free(pip->outfile->cmd);
		if (pip->paths)
			free(pip->paths);
		if (pip->infile)
			free(pip->infile);
		if (pip->outfile)
			free(pip->outfile);
		free(pip);
	}
}
// open: Open files (in and out).
// pipe: Create a pipe to connect cmd1 and cmd2.
// fork: Create two child processes.
// dup2: Redirect file descriptors between the processes.
// execve: Run the commands in the children.
// waitpid: Wait for child processes to finish.

// ./pip in cmd1 cmd2 out

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

t_pipe *init_structs(char **argv, char **envp, t_pipe **pip)
{
	t_pipe *pip;

	pip = (t_pipe *)malloc(sizeof(t_pipe));
	if (!pip)
		error_exit("malloc");

	pip->in = (t_cmd *)malloc(sizeof(t_cmd));
	pip->out = (t_cmd *)malloc(sizeof(t_cmd));
	if (!pip->in || !pip->out)
		error_exit("Malloc\n");
	pip->in->fd = ft_open('R', argv[1]);
	pip->in->name = argv[1];
	pip->out->fd = ft_open('W', argv[4]);
	pip->out->name = argv[4];
	pip->in->cmd = ft_split(argv[2], ' ');
	pip->out->cmd = ft_split(argv[3], ' ');
	pip->paths = ft_split(getenv_paths(envp), ':');
	
	// perror("< %s %s | %s > %s\n", pip->in->name, pip->in->cmd[0], pip->out->cmd[0], pip->out->name);
	return (pip);
}




int main(int argc, char **argv, char **envp) 
{
	t_pipe *pip;
	
	check_args(argc, argv);
	init_structs(argv, envp, &pip);

    if (pipe(pip->fd) == -1)
        error_exit("pipe");

    pip->in->pid = fork();
    if (pip->in->pid == -1)
        error_exit("fork");

    if (pip->in->pid == 0) 
	{
        pip->fdrd = open(argv[1], O_RDONLY);
        if (pip->fdrd == -1)
            error_exit("open input_file");

        dup2(pip->fdrd, STDIN_FILENO);
        dup2(pip->fd[1], STDOUT_FILENO);
        close(pip->fdrd);
        close(pip->fd[0]);
        close(pip->fd[1]);

        char *cmd1[] = {"/bin/sh", "-c", argv[2], NULL}; // Execute cmd1
        execv("/bin/sh", cmd1);
        error_exit("execv cmd1");
    }

    pip->out->pid = fork();
    if (pip->out->pid == -1)
        error_exit("fork");

    if (pip->out->pid == 0) 
	{
        pip->fdwr = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pip->fdwr == -1)
            error_exit("open output_file");

        dup2(pip->fd[0], STDIN_FILENO);
        dup2(pip->fdwr, STDOUT_FILENO);
        close(pip->fdwr);
        close(pip->fd[0]);
        close(pip->fd[1]);

        char *cmd2[] = {"/bin/sh", "-c", argv[3], NULL}; // Execute cmd2
        execv("/bin/sh", cmd2);
        error_exit("execv cmd2");
    }

    // Parent process
    close(pip->fd[0]);
    close(pip->fd[1]);

    waitpid(pip->in->pid, NULL, 0); // Wait for first child
    waitpid(pip->out->pid, NULL, 0); // Wait for second child

	free(pip);

    return 0;
}
