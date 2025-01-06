/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:48:03 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/06 04:30:27 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_free(t_args *args, int close_fd)
{
	if (close_fd >= 1)
	{
		if (args->fd_in != -1)
			close(args->fd_in);
		if (args->fd_out != -1)
			close(args->fd_out);
		if (close_fd == 1)
			close(args->pipefd[0]);
		if (close_fd == 2)
			close(args->pipefd[1]);	
	}
	if (args)
		free(args);
	args = NULL;
}

void	exit_error(t_args *args, int close_fd, char *msg, int status)
{
	ft_free(args, close_fd);
	if (msg)
		perror(msg);
	exit(status);
}
