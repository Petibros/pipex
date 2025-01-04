/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:49:50 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/04 17:11:46 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	parent(t_args *args, char **argv, char **envp)
{
	char	*path;
	char	**cmd;

	close(args->pipefd[1]);
	dup2(args->pipefd[0], 0);
	dup2(args->fd_out, 1);
	cmd = ft_split(argv[1], ' ');
	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = get_path(envp, cmd);
	ft_free(args, 0);
	if (path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	return (0);
}

static int	child(t_args *args, char **argv, char **envp)
{
	char	*path;
	char	**cmd;

	close(args->pipefd[0]);
	dup2(args->fd_in, 0);
	dup2(args->pipefd[1], 1);
	cmd = ft_split(argv[0], ' ');
	if (ft_strchr(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else
		path = get_path(envp, cmd);
	ft_free(args, 0);
	if (path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	return (0);
}

static void	here_doc(t_args *args)
{
	char	*line;

	pipe(args->pipedoc);
	line = get_next_line(0);
	while (ft_strncmp(args->limiter, line, ft_strlen(line) - 1))
	{
		write(args->pipedoc[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	args->fd_in = args->pipedoc[0];
	close(args->pipedoc[1]);
	free(line);
}

static int	pipex(t_args *args, char **argv, char **envp)
{
	int		pid;

	if (args->limiter)
		here_doc(args);
	pipe(args->pipefd);
	pid = fork();
	if (pid == 0)
	{
		if (!child(args, argv, envp))
			return (-1);
	}
	if (pid > 0)
	{
		if (!parent(args, argv, envp))
			return (-1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		start;
	int		return_value;

	if (argc < 4 || !envp)
	{
		write(2, "Missing argument(s)\n", 20);
		return (1);
	}
	args = malloc(sizeof(t_args));
	if (!args)
	{
		perror("In init_args");
		exit(1);
	}
	args->limiter = NULL;
	start = parsing(argv, argc, args);
	if (!start)
		exit_error(args, 0, "In init_fd function");
	return_value = pipex(args, &argv[start], envp);
	if (return_value == -1)
		exit_error(args, 2, "In pipex function, command not found");
//	printf("%d", return_value);
	return (return_value);
}
