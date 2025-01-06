/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:56:01 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/06 04:38:51 by sacgarci         ###   ########.fr       */
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
	int		pipedoc[2];
	int		pipefd[2];
	int		wait_pid;
	int		wait_status;
	int		start;
}	t_args;

char	*get_path(char **envp, char **cmd);
void	exit_error(t_args *args, int close_fd, char *msg, int status);
void	ft_free(t_args *args, int close_fd);
int		parsing(char **argv, int argc, t_args *args);

#endif
