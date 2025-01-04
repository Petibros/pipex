/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:49:50 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/21 20:06:10 by sacgarci         ###   ########.fr       */
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
//	ft_free(args, 0);
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
//	ft_free(args, 0);
	if (path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	return (0);
}

static void	here_doc(t_args *args)
{
	int		pipe_doc[2];
	char	*line;

	pipe(pipe_doc);
	line = get_next_line(0);
	while (ft_strncmp(args->limiter, line, ft_strlen(line) - 1))
	{
		printf("%u\n", 1);
		write(pipe_doc[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	args->fd_in = pipe_doc[0];
	free(line);
}

static int	pipex(t_args *args, char **argv, char **envp)
{
	int		pid;
	int		pid2;
	int		status;

	status = 0;
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
		pid2 = fork();
		if (pid2 > 0)
			if (!parent(args, argv, envp))
				return (-1);
		if (pid2 == 0)
			waitpid(pid2, &status, 0);
	}
	return (status);
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
