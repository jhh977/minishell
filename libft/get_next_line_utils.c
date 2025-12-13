/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:07:05 by jhijazi           #+#    #+#             */
/*   Updated: 2025/09/11 13:24:56 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char	*ft_strdup(const char *src)
// {
// 	char	*dest;
// 	int		i;

// 	dest = malloc(ft_str_len(src)+1);
// 	if (!dest)
// 		return (0);
// 	i = 0;
// 	while (src[i] != '\0')
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

size_t	ft_str_len(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*append_new_buffer(char *rem, char *temp)
{
	size_t	i;
	size_t	j;
	char	*a;

	i = 0;
	j = 0;
	if (!rem)
		rem = ft_strdup("");
	a = malloc(ft_str_len(rem) + ft_str_len(temp) + 1);
	if (!a)
		return (NULL);
	while (rem[i])
	{
		a[i] = rem[i];
		i++;
	}
	while (temp[j])
	{
		a[i + j] = temp[j];
		j++;
	}
	a[i + j] = '\0';
	free(rem);
	return (a);
}

char	*extract_line(char *rem)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	if (!rem)
		return (NULL);
	while (rem[i] && rem[i] != '\n')
		i++;
	if (rem[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = rem[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_rem(char *rem)
{
	int		i;
	char	*new_rem;

	if (!rem)
		return (NULL);
	i = 0;
	while (rem[i] && rem[i] != '\n')
		i++;
	if (!rem[i])
	{
		free(rem);
		return (NULL);
	}
	i++;
	new_rem = ft_strdup(rem + i);
	free(rem);
	return (new_rem);
}
