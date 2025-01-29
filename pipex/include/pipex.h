/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/29 11:55:49 by vvoronts         ###   ########.fr       */
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


// No errors
# define SUCCESS         	0
 // Generic errors
# define ERROR   			1
# define FAIL   			-1
 // Command not found
# define EXECUTE			127

typedef enum e_errno
{
	NOER,
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

// -- INIT --
void	validate_args(int argc, char **argv);
void	init_structs(t_context **p, char **argv, char **envp);
// -- RUN --
void	open_pipe(t_context *p); 
int		ft_open(int flag, char *file);
void	run_children(t_context *p, char **envp);
// -- COMMANDS --
char	*getenv_paths(char **envp);
char	*peek(char **paths, char *cmd);
// -- END --
void	close_pipe(t_context *p);
int		wait_processes(t_context *p);
void	perror_message(t_errno err);
void	error_exit(t_errno err, t_context *p);
void	cleanup(t_context *p);

#endif