/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/27 18:29:43 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "elibft.h"
# include <fcntl.h>
# include <unistd.h>
# include <errno.h> 
# include <sys/wait.h>

#define FAIL -1
#define SUCESS 0

typedef enum e_errno
{
	ARGS,
	NO_FILE,
	NO_CMD,
	NO_ACCESS,
	OPEN,
	DUP,
	PIPE,
	FORK,
	EXEC,
	PATH,
	MALLOC
} t_errno;


typedef struct s_cmd
{
	pid_t	pid;
	int		fd;
	char	**cmd;
	char	*file;
	char 	*path;
}	t_cmd;

typedef struct s_context
{
	t_cmd 	*in;
	t_cmd 	*out;
	int 	read;
	int 	write;
	char	**paths;
	
} t_context;


void	init_structs(t_context **p, char **argv, char **envp);
void	error_exit(t_errno err, t_context *p);
void	cleanup(t_context *p);
void	validate_args(int argc, char **argv);

int		ft_open(int flag, char *file, t_context *p);
void	close_pipe(t_context *p);
void	open_pipe(t_context *p);
int		run_children(t_context *p, char **envp);

char	*getenv_paths(char **envp, t_context *p);
char	*peek(char **paths, char *cmd, t_context *p);

// int		wait_processes(t_context *p);


#endif