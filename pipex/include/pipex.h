/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/28 11:56:07 by vvoronts         ###   ########.fr       */
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

# define FAIL -1
# define SUCESS 0

typedef enum e_errno
{
	ARGS,
	NO_FILE,
	NO_CMD,
	FILE_FAIL,
	OPEN,
	DUP,
	PIPE,
	FORK,
	EXEC,
	PATH,
	MALLOC
}	t_errno;

typedef struct s_cmd
{
	int		fd;
	pid_t	pid;
	char	*path;
	char	*file;
	char	**cmd;
}	t_cmd;

typedef struct s_context
{
	int		read;
	int		write;
	t_cmd	*in;
	t_cmd	*out;
	char	**paths;
}	t_context;

void	init_structs(t_context **p, char **argv, char **envp);
void	error_exit(t_errno err, t_context *p);
void	cleanup(t_context *p);
void	validate_args(int argc, char **argv);
int		ft_open(int flag, char *file, t_context *p);
void	close_pipe(t_context *p);
void	open_pipe(t_context *p);
void	run_children(t_context *p, char **envp);
char	*getenv_paths(char **envp, t_context *p);
char	*peek(char **paths, char *cmd, t_context *p);
int		wait_processes(t_context *p);
void	perror_message(t_errno err);

#endif