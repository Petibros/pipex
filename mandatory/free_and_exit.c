/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:48:03 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/05 00:00:02 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
