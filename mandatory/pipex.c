/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:49:50 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/06 04:36:24 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	first(t_args *args, char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	path = NULL;
	if (args->fd_in == -1)
		exit_error(args, 2, NULL, 1);
	dup2(args->fd_in, 0);
	dup2(args->pipefd[1], 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (!cmd || !cmd[0] || !path)
	{
		free_char_array(cmd);
		exit_error(args, 2, "First command, command not found", 127);
	}
	execve(path, cmd, envp);
	if (path)
		free(path);
	free_char_array(cmd);
	exit_error(args, 2, "First command, execve error", 127);
}

static void	second(t_args *args, char *argv, char **envp)
{
	char	*path;
	char	**cmd;

	path = NULL;
	if (args->fd_out == -1)
		exit_error(args, 1, NULL, 1);
	dup2(args->pipefd[0], 0);
	dup2(args->fd_out, 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (!cmd || !cmd[0] || !path)
	{
		free_char_array(cmd);
		exit_error(args, 1, "Second command, command not found", 127);
	}
	execve(path, cmd, envp);
	if (path)
		free(path);
	free_char_array(cmd);
	exit_error(args, 1, "Second command, execve error", 127);
}

static void	pipex(t_args *args, char **argv, char **envp)
{
	int	pid;
	int	i;

	i = 0;
	pipe(args->pipefd);
	while (i < 2)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				close(args->pipefd[0]);
				first(args, argv[2 + i], envp);
			}
			close(args->pipefd[1]);
			second(args, argv[2 + i], envp);
		}
		++i;
	}
	close(args->pipefd[0]);
	close(args->pipefd[1]);
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
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		final_status;
	int		wpid;

	if (argc != 5 || !envp)
	{
		write(2, "Missing/Too many argument(s)\n", 29);
		exit(1);
	}
	args = init_args();
	parsing(argv, args);
	pipex(args, argv, envp);
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
