/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:49:50 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/04 23:58:22 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	parent(t_args *args, char **argv, char **envp)
{
	char	*path;
	char	**cmd;

	close(args->pipefd[0]);
	dup2(args->fd_in, 0);
	dup2(args->pipefd[1], 1);
	cmd = ft_split(argv[0], ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	ft_free(args, 0);
	if (cmd && cmd[0] && path)
	{
		execve(path, cmd, envp);
		free(path);
	}
	perror("In child process, Command not found");
	free_char_array(cmd);
	return (0);
}

static int	child(t_args *args, char **argv, char **envp)
{
	char	*path;
	char	**cmd;

	close(args->pipefd[1]);
	dup2(args->pipefd[0], 0);
	dup2(args->fd_out, 1);
	cmd = ft_split(argv[1], ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	ft_free(args, 0);
	if (cmd && cmd[0] && path)
	{
		execve(path, cmd, envp);
		free(path);
	}
	perror("In child process, Command not found");
	free_char_array(cmd);
	return (0);
}

static int	pipex(t_args *args, char **argv, char **envp)
{
	int	pid;
	int	pid2;
	int	status;

	status = 0;
	pipe(args->pipefd);
	pid = fork();
	if (pid == 0)
		parent(args, argv, envp);
	if (pid > 0)
	{
		pid2 = fork();
		if (pid2 == 0)
			child(args, argv, envp);
	}
	waitpid(-1, &status, 0);
	return (status);
}

t_args	*init_args(void)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
	{
		perror("In init_args");
		exit(1);
	}
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		start;
	int		status;

	if (argc != 5 || !envp)
	{
		write(2, "Missing/Too many argument(s)\n", 29);
		return (1);
	}
	args = init_args();
	start = parsing(argv, argc, args);
	if (!start)
		exit_error(args, 0, "In init_fd function", 1);
	status = pipex(args, &argv[start], envp);
		exit_error(args, 1, NULL, status);
	return (status);
}
