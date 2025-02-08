/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/02/08 09:33:59 by vvoronts         ###   ########.fr       */
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
# define DENIED				126
# define EXEC				127
// Errors
# define NO_CMD				127
# define ARGS				10
# define NO_FILE			11
# define NO_PERM			12
# define FILE_FAIL			13
# define MALLOC				14
# define FAIL   			-1
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
void	wrapped(int result, int code, t_context *p);
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