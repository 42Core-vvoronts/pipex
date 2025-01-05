/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvoronts <vvoronts@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 15:03:15 by vvoronts          #+#    #+#             */
/*   Updated: 2025/01/05 15:27:28 by vvoronts         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char **argv, char **envp)
{
	
    // Step 1: Validate arguments
	if is_valid(argc, argv)
		parse_args(argc, argv);
    	// Step 2: Parse arguments
	else
		// exit with error
    // Step 3: Handle here-documents

    // Step 4: Open input/output files

    // Step 5: Set up pipes for commands

    // Step 6: Fork processes to execute commands

    // Step 7: Cleanup and finish
		close_fds() // close all file descriptors
		free_mem() // free all allocated memory
    	exit() // exit with success
}
