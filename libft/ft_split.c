/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sacgarci <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 03:10:42 by sacgarci          #+#    #+#             */
/*   Updated: 2025/01/06 04:10:59 by sacgarci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_quotes(const char *s, int *i)
{
	int	n;

	n = 0;
	if (s[*i] == 39)
	{
		*i += 1;
		while (s[*i] && s[*i] != 39)
		{
			*i += 1;
			n++;
		}
		if (!s[*i])
			return (-1);
	}
	return (n);
}

static void	ft_strncpy(char *dest, char const *src, int n)
{
	int	i;

	i = 0;
	while (src[i] && i < n)
	{
		if (src[i + 1] == 39)
			--n;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static int	fill_array(char const *s, char c, char **array, int count)
{
	int	i;
	int	j;
	int	start;

	start = 0;
	j = 0;
	i = 0;
	while (j < count)
	{
		start += skip_quotes(s, &i);
		if (s[i] == c && s[i - 1] == c)
			start = -1;
		else if (s[i] == c || s[i] == '\0')
		{
			array[j] = malloc((start + 1) * sizeof(char));
			if (!array[j])
				return (j);
			ft_strncpy(array[j++], &s[i - start], start);
			start = -1;
		}
		i++;
		start++;
	}
	array[j] = NULL;
	return (-1);
}

static int	numstring(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (skip_quotes(s, &i) == -1)
			return (-1);
		else if (s[i] == c && s[i + 1] != c)
			count++;
		else if (s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == c && c != '\0')
		i++;
	count = numstring(&s[i], c);
	if (count == -1)
	{
		write(2, "Uneven quotes\n", 14);
		return (NULL);
	}
	array = malloc((count + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	count = fill_array(&s[i], c, array, count);
	if (count >= 0 && !array[count])
	{
		free_char_array(array);
		return (NULL);
	}
	return (array);
}
