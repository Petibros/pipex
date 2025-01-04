/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:56:01 by sacgarci          #+#    #+#             */
/*   Updated: 2024/12/08 23:03:37 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_args
{
	char	*limiter;
	int		n_cmd;
	int		fd_in;
	int		fd_out;
	int		pipefd[2];
}	t_args;

char	*get_path(char **envp, char **cmd);
void	free_char_array(char **array);
void	exit_error(t_args *args, int close_fd, char *msg);
void	ft_free(t_args *args, int close_fd);
int		parsing(char **argv, int argc, t_args *args);
int		init_fd(char **argv, int argc, t_args *args);

#endif
