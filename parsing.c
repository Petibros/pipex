/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:46:10 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/01 16:41:02 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_fd(char **argv, int argc, t_args *args)
{
	int	fd_in;
	int	fd_out;

	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		fd_in = 0;
	else
		fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		return (0);
	args->fd_in = fd_in;
	fd_out = open(argv[argc - 1], O_RDWR | O_CREAT, S_IRWXU);
	if (fd_out == -1)
	{
		close(fd_in);
		return (0);
	}
	args->fd_out = fd_out;
	return (1);
}

char	*get_path(t_args *args, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*to_join;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0 && envp[i])
		i++;
	paths = ft_split(&envp[i][5], ':');
	i = 0;
	to_join = ft_strjoin("/", args->cmd[0]);
	while (paths && paths[i])
	{
		path = ft_strjoin(paths[i], to_join);
		if (!path)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	free(to_join);
	free_char_array(paths);
	if (!paths || !paths[i])
		return (NULL);
	return (path);
}

int	parsing(char **argv, int argc, t_args *args)
{
	if (!init_fd(argv, argc, args))
		return (0);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		args->n_cmd = argc - 4;
		args->limiter = argv[2];
		return (3);
	}
	args->n_cmd = argc - 3;
	return (2);
}
