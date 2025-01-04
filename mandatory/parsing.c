/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:46:10 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/04 18:41:01 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_fd(char **argv, int argc, t_args *args)
{
	args->fd_in = open(argv[1], O_RDONLY);
	if (args->fd_in == -1)
		return (0);
	args->fd_out = open(argv[argc - 1], O_RDWR | O_TRUNC | O_CREAT, S_IRWXU);
	if (args->fd_out == -1)
	{
		close(args->fd_in);
		return (0);
	}
	return (1);
}

char	*get_path(char **envp, char **cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*to_join;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(&envp[i][5], ':');
	i = 0;
	to_join = ft_strjoin_libft("/", cmd[0]);
	while (paths && paths[i])
	{
		path = ft_strjoin_libft(paths[i], to_join);
		if (!path || access(path, F_OK) == 0)
			break ;
		free(path);
		i++;
	}
	free(to_join);
	if (!paths || !paths[i] || !path)
		path = NULL;
	free_char_array(paths);
	return (path);
}

int	parsing(char **argv, int argc, t_args *args)
{
	if (!init_fd(argv, argc, args))
		return (0);
	args->n_cmd = argc - 3;
	return (2);
}
