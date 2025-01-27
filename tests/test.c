#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_pipe
{
	int fd[2];
	pid_t pid1;
	pid_t pid2;
	int   fdr;
	int   fdw;
	char **paths;


} t_pipe;

void error_exit(char *message) 
{
    perror(message);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp) 
{
	t_pipe *pip;
	
    if (argc != 5) 
        error_exit("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n");
	pip = malloc(sizeof(t_pipe));
	if (!pip)
		error_exit("malloc");
	pip->paths = ft_split(getenv_paths(envp), ':');

    if (pipe(pip->fd) == -1)
        error_exit("pipe");

    pip->pid1 = fork();
    if (pip->pid1 == -1)
        error_exit("fork");

    if (pip->pid1 == 0) 
	{
        pip->fdr = open(argv[1], O_RDONLY);
        if (pip->fdr == -1)
            error_exit("open input_file");

        dup2(pip->fdr, STDIN_FILENO);
        dup2(pip->fd[1], STDOUT_FILENO);
        close(pip->fdr);
        close(pip->fd[0]);
        close(pip->fd[1]);

        char *cmd1[] = {"/bin/sh", "-c", argv[2], NULL}; // Execute cmd1
        execv("/bin/sh", cmd1);
        error_exit("execv cmd1");
    }

    pip->pid2 = fork();
    if (pip->pid2 == -1)
        error_exit("fork");

    if (pip->pid2 == 0) 
	{
        pip->fdw = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (pip->fdw == -1)
            error_exit("open output_file");

        dup2(pip->fd[0], STDIN_FILENO);
        dup2(pip->fdw, STDOUT_FILENO);
        close(pip->fdw);
        close(pip->fd[0]);
        close(pip->fd[1]);

        char *cmd2[] = {"/bin/sh", "-c", argv[3], NULL}; // Execute cmd2
        execv("/bin/sh", cmd2);
        error_exit("execv cmd2");
    }

    // Parent process
    close(pip->fd[0]);
    close(pip->fd[1]);

    waitpid(pip->pid1, NULL, 0); // Wait for first child
    waitpid(pip->pid2, NULL, 0); // Wait for second child

	free(pip);

    return 0;
}
