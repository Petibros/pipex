/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:48:03 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/01 10:02:45 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i++;
		}
		free(array);
	}
}

void	ft_free(t_args *args, int close_fd)
{
	if (close_fd == 1)
	{
		close(args->fd_in);
		close(args->fd_out);
	}
	if (close_fd != 2 && args->limiter)
		free(args->limiter);
	if (close_fd != 2)
		free(args);
	args = NULL;
}

void	exit_error(t_args *args, int close_fd, char *msg)
{
	ft_free(args, close_fd);
	perror(msg);
	exit(1);
}
