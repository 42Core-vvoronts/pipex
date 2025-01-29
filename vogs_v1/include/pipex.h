/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/29 17:05:19 by vvoronts         ###   ########.fr       */
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

// Main Exitcodes
# define SUCCESS			0
# define STERROR   			1
// # define EXECUTE			127
// Errors
# define EXEC				127
# define NO_CMD				127
# define ARGS				1
# define NO_FILE			1
# define FILE_FAIL			1
# define OPEN				1
# define DUP				1
# define PIPE				1
# define FORK				1
# define PATH				1
# define MALLOC				1
# define FAIL   			-1

// typedef enum e_errno
// {
// 	NOER,
// 	ARGS,
// 	NO_FILE,
// 	NO_CMD,
// 	FILE_FAIL,
// 	OPEN,
// 	DUP,
// 	PIPE,
// 	FORK,
// 	EXEC,
// 	PATH,
// 	MALLOC
// }	int;
// Child
typedef struct s_cmd
{
	int		fd;
	pid_t	pid;
	char	*path;
	char	*file;
	char	**cmd;
}	t_cmd;
// Pipe
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
void	perror_message(int err);
void	error_exit(int err, t_context *p);
void	cleanup(t_context *p);

#endif