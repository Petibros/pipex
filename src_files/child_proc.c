/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_proc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:30:52 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 01:53:37 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first(t_args *args, char *argv, char **envp, int is_even)
{
	char	*path;
	char	**cmd;

	path = NULL;
	if (args->fd_in == -1)
		exit_error(args, 1 + is_even, NULL, 1);
	dup2(args->fd_in, 0);
	dup2(args->pipefd_1[1], 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (cmd && cmd[0] && path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	if (!path || *path != '.' || path[1] != '/' || access(&path[2], F_OK) != 0)
	{
		if (path)
			free(path);
		exit_error(args, 1, "First command, command not found", 127);
	}
	free(path);
	exit_error(args, 1, "First command, permission denied", 126);
}

void	last_even(t_args *args, char *argv, char **envp, int is_even)
{
	char	*path;
	char	**cmd;

	path = NULL;
	if (args->fd_out == -1)
		exit_error(args, 4 + is_even, NULL, 1);
	dup2(args->pipefd_2[0], 0);
	dup2(args->fd_out, 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (cmd && cmd[0] && path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	if (!path || *path != '.' || path[1] != '/' || access(&path[2], F_OK) != 0)
	{
		if (path)
			free(path);
		exit_error(args, 4 + is_even, "Last command, command not found", 127);
	}
	free(path);
	exit_error(args, 4 + is_even, "Last command, permission denied", 126);
}

void	last_uneven(t_args *args, char *argv, char **envp, int is_even)
{
	char	*path;
	char	**cmd;

	path = NULL;
	if (args->fd_out == -1)
		exit_error(args, 4 + is_even, NULL, 1);
	dup2(args->pipefd_1[0], 0);
	dup2(args->fd_out, 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (cmd && cmd[0] && path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	if (!path || *path != '.' || path[1] != '/' || access(&path[2], F_OK) != 0)
	{
		if (path)
			free(path);
		exit_error(args, 4 + is_even, "Last command, command not found", 127);
	}
	free(path);
	exit_error(args, 4 + is_even, "Last command, permission denied", 126);
}

void	even(t_args *args, char *argv, char **envp, int is_even)
{
	char	*path;
	char	**cmd;

	path = NULL;
	dup2(args->pipefd_2[0], 0);
	dup2(args->pipefd_1[1], 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (cmd && cmd[0] && path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	write(2, argv, ft_strlen(argv));
	if (!path || *path != '.' || path[1] != '/' || access(&path[2], F_OK) != 0)
	{
		if (path)
			free(path);
		exit_error(args, 2 + is_even, " : Command not found", 127);
	}
	free(path);
	exit_error(args, 2 + is_even, " : permission denied", 126);
}

void	uneven(t_args *args, char *argv, char **envp, int is_even)
{
	char	*path;
	char	**cmd;

	path = NULL;
	dup2(args->pipefd_1[0], 0);
	dup2(args->pipefd_2[1], 1);
	cmd = ft_split(argv, ' ');
	if (cmd && cmd[0] && ft_strchr_libft(cmd[0], '/'))
		path = ft_strdup(cmd[0]);
	else if (cmd && cmd[0])
		path = get_path(envp, cmd);
	if (cmd && cmd[0] && path)
		execve(path, cmd, envp);
	free_char_array(cmd);
	write(2, argv, ft_strlen(argv));
	if (!path || *path != '.' || path[1] != '/' || access(&path[2], F_OK) != 0)
	{
		if (path)
			free(path);
		exit_error(args, 2 + is_even, " : Command not found", 127);
	}
	free(path);
	exit_error(args, 2 + is_even, " : permission denied", 126);
}
