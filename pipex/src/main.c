/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:59:11 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/29 17:17:55 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_context	*p;
	int			exitcode;

	exitcode = 0;
	validate_args(argc, argv);
	init_structs(&p, argv, envp);
	open_pipe(p);
	run_children(p, envp);
	close_pipe(p);
	exitcode = wait_processes(p);
	cleanup(p);
	return (exitcode);
}
