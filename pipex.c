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

#include <stdio.h>
static int	pipex(t_args *args, char **argv, char **envp)
{
	int		pid;
	int		pid2;
	char	*path;

	pipe(args->pipefd);
	pid = fork();
	if (pid == 0)
	{
		printf("fils\n");
		close(args->pipefd[0]);
        dup2(args->fd_in, 0);
        dup2(args->pipefd[1], 1);
        args->cmd = ft_split(argv[0], ' ');
        if (args->cmd[0][0] == '/')
            path = ft_strdup(args->cmd[0]);
        else
            path = get_path(args, envp);
        execve(path, args->cmd, envp);	
	}
	if (pid > 0)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			printf("fils du pere\n");
	        close(args->pipefd[1]);
    	    dup2(args->pipefd[0], 0);
	        dup2(args->fd_out, 1);
   	    	args->cmd = ft_split(argv[1], ' ');
        	if (args->cmd[0][0] == '/')
            	path = ft_strdup(args->cmd[0]);
        	else
            	path = get_path(args, envp);
        	execve(path, args->cmd, envp);
		}
		printf("pere\n");
	}
	return (1);
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
	args->cmd = NULL;
	args->limiter = NULL;
	return (args);
}

int	main(int argc, char **argv, char **envp)
{
	t_args	*args;
	int		start;

	if (argc < 4 || !envp)
	{
		write(1, "Missing argument(s)\n", 20);
		return (1);
	}
	args = init_args();
	start = parsing(argv, argc, args);
	if (!start)
		exit_error(args, 0, "In init_fd function");
	if (!pipex(args, &argv[start], envp))
		exit_error(args, 1, "In pipex function");
	ft_free(args, 1);
	return (0);
}
