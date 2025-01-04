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

#include "pipex.h"

static int	parent(t_args *args, char **argv, char **envp)
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

static int	child(t_args *args, char **argv, char **envp)
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

static int	pipex(t_args *args, char **argv, char **envp)
{
	int		pid;

	pipe(args->pipefd);
	pid = fork();
	if (pid == 0)
	{
		child(args, argv, envp);
	}
	if (pid > 0)
	{
		parent(args, argv, envp);
	}
	return (0);
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
	args->limiter = NULL;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		start;

	if (argc < 4 || !envp)
	{
		write(2, "Missing argument(s)\n", 20);
		return (1);
	}
	args = init_args();
	start = parsing(argv, argc, args);
	if (!start)
		exit_error(args, 0, "In init_fd function");
	if (!pipex(args, &argv[start], envp))
		exit_error(args, 2, "In pipex function, command not found");
	return (0);
}
