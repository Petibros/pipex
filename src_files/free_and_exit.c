/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:48:03 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 16:02:14 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close(int fds[2])
{
	close(fds[0]);
	close(fds[1]);
}

void	close_fds(t_args *args, int close_fd)
{
	if (close_fd >= 1 && args->fd_in != -1)
		close(args->fd_in);
	if (close_fd >= 1 && args->fd_out != -1)
		close(args->fd_out);
	if (close_fd == 5)
		close(args->pipefd_1[0]);
	if (close_fd == 4)
		close(args->pipefd_2[0]);
	if (close_fd == 3)
	{
		close(args->pipefd_1[0]);
		close(args->pipefd_2[1]);
	}
	if (close_fd == 2)
	{
		close(args->pipefd_1[1]);
		close(args->pipefd_2[0]);
	}
	if (close_fd == 1)
		close(args->pipefd_1[1]);
}

void	ft_free(t_args *args, int close_fd)
{
	close_fds(args, close_fd);
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
