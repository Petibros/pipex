/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 01:01:25 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/07 15:27:16 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256

# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd, char *limiter);
int		ft_strnlen(char *str, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_calloc(int nmemb, int size);
void	ft_strcpy(char *dest, char *src);
int		ft_strchr(char *src, char c);

#endif
