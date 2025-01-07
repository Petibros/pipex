/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 06:56:01 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 01:04:31 by sacgarci         ###   ########.fr       */
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
	int		pipefd_2[2];
	int		pipefd_1[2];
	int		wait_pid;
	int		wait_status;
	int		start;
}	t_args;

void	find_proc(t_args *args, char **argv, char **envp, int n);
void	proc_even(t_args *args, char **argv, char **envp, int n);
void	here_doc(t_args *args);
void	ft_close(int fds[2]);
void	first(t_args *args, char *argv, char **envp, int is_even);
void	last_even(t_args *args, char *argv, char **envp, int is_even);
void	last_uneven(t_args *args, char *argv, char **envp, int is_even);
void	even(t_args *args, char *argv, char **envp, int is_even);
void	uneven(t_args *args, char *argv, char **envp, int is_even);
char	*get_path(char **envp, char **cmd);
void	exit_error(t_args *args, int close_fd, char *msg, int status);
void	ft_free(t_args *args, int close_fd);
int		parsing(char **argv, int argc, t_args *args);

#endif
