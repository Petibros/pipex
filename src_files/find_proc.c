/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 01:01:51 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 15:58:20 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	proc_even(t_args *args, char **argv, char **envp, int n)
{
	if (n == 0)
	{
		close(args->fd_out);
		close(args->pipefd_1[0]);
		first(args, argv[n], envp, n % 2);
	}
}

void	find_proc(t_args *args, char **argv, char **envp, int n)
{
	if (n % 2 == 0)
	{
		close(args->fd_in);
		close(args->pipefd_2[1]);
		if (n == args->n_cmd - 1)
		{
			ft_close(args->pipefd_1);
			last_even(args, argv[n], envp, n % 2);
		}
		close(args->fd_out);
		close(args->pipefd_1[0]);
		even(args, argv[n], envp, n % 2);
	}
	close(args->fd_in);
	close(args->pipefd_1[1]);
	if (n == args->n_cmd - 1)
	{
		ft_close(args->pipefd_2);
		last_uneven(args, argv[n], envp, n % 2);
	}
	close(args->fd_out);
	close(args->pipefd_2[0]);
	uneven(args, argv[n], envp, n % 2);
}
