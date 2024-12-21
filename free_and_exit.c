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

int	ft_free(t_args *args, int close_fd)
{
	free_char_array(args->cmd);
	if (close_fd)
	{
		close(args->fd_in);
		close(args->fd_out);
	}
	free(args);
	return (1);
}

void	exit_error(t_args *args, int close_fd, char *msg)
{
	ft_free(args, close_fd);
	perror(msg);
	exit(1);
}
