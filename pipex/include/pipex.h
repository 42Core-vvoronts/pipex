/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:16:06 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/05 17:40:46 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>

# define SUCCESS 0
# define AC_ERR 2
# define PIPE_ERR 3
# define FORK_ERR 4
# define DUP_ERR 5
# define ENV_ERR 6
# define MALLOC_ERR 7
# define FILE1_ERR 8
# define FILE2_ERR 9
# define CMD_ERR 126
# define CMD_PATH_ERR 127

#endif