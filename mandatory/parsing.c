/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 08:46:10 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/05 23:31:04 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	path_exists(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (!envp[i])
		return (-1);
	return (i);
}

char	*get_path(char **envp, char **cmd)
{
	int		i;
	char	**paths;
	char	*path;
	char	*to_join;

	i = path_exists(envp);
	if (i == -1)
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

int	parsing(char **argv, t_args *args)
{
	args->fd_in = open(argv[1], O_RDONLY);
	if (args->fd_in == -1)
		perror("In parsing, fd_in");
	args->fd_out = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, S_IRWXU);
	if (args->fd_out == -1)
		perror("In parsing, fd_out");
	return (0);
}
