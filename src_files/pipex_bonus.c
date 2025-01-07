/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:49:50 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 01:36:04 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	pipex(t_args *args, char **argv, char **envp)
{
	int	pid;
	int	i;

	i = 0;
	while (i < args->n_cmd)
	{
		if (i != 0 && i % 2 == 0)
			ft_close(args->pipefd_1);
		if (i % 2 == 0)
			pipe(args->pipefd_1);
		if (i != 1 && i % 2 == 1)
			ft_close(args->pipefd_2);
		if (i % 2 == 1)
			pipe(args->pipefd_2);
		pid = fork();
		if (pid == 0)
		{
			proc_even(args, argv, envp, i);
			find_proc(args, argv, envp, i);
		}
		++i;
	}
	ft_close(args->pipefd_1);
	ft_close(args->pipefd_2);
}

void	here_doc(t_args *args)
{
	char	*line;

	pipe(args->pipedoc);
	write(1, "heredoc> ", 9);
	line = get_next_line(0);
	while (ft_strlen(line) - 1 != ft_strlen(args->limiter)
		|| ft_strncmp(args->limiter, line, ft_strlen(line) - 1))
	{
		write(args->pipedoc[1], line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 9);
		line = get_next_line(0);
	}
	args->fd_in = args->pipedoc[0];
	close(args->pipedoc[1]);
	free(line);
}

static t_args	*init_args(void)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
	{
		perror("In init_args");
		exit(1);
	}
	args->wait_pid = 1;
	args->wait_status = 1;
	args->limiter = NULL;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		final_status;
	int		wpid;

	if (argc < 5 || ((ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
			&& argc < 6) || !envp)
	{
		write(2, "Missing argument(s)\n", 20);
		return (1);
	}
	args = init_args();
	args->start = parsing(argv, argc, args);
	pipex(args, &argv[args->start], envp);
	wpid = waitpid(-1, &args->wait_status, 0);
	while (wpid > 0)
	{
		if (args->wait_pid < wpid)
		{
			final_status = args->wait_status;
			args->wait_pid = wpid;
		}
		wpid = waitpid(-1, &args->wait_status, 0);
	}
	ft_free(args, 1);
	exit(WEXITSTATUS(final_status));
}
