/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/26 18:13:51 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "ft_printf.h"
# include "elibft.h"
# include <fcntl.h>
# include <unistd.h> 
# include <sys/wait.h>

#define SUCCESS          0
#define SYNTAX_FAIL      1
#define CMD_FAIL    	 2
#define OPEN_FAIL		 3
#define EXEC_FAIL        4
#define PIPE_FAIL        5
#define FOUND_FAIL       6
#define MALLOC_FAIL		 7


typedef struct s_cmd
{
	int		fd;
	int 	pid;
	char	**cmd;
	char	*name;
}	t_cmd;

typedef struct s_pipe
{
	t_cmd 		*infile; //left
	t_cmd 		*outfile; //right
	int 		newfd[2];
	char		**paths;
	
} t_pipe;


// -- ERRORS --
int		valid_args(int argc, char **argv);
void	handle_error(int errno, t_pipe *pip);
void	cleanup(t_pipe *pip);

// -- PIPEX --
t_pipe	*init_pipe(void);
void	connect_files(t_pipe *pip);
void fork_first_child(t_pipe *pip, char **envp);
void fork_second_child(t_pipe *pip, char **envp);


#endif