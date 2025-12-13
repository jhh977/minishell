/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:01:45 by jhijazi           #+#    #+#             */
/*   Updated: 2025/08/06 16:01:05 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *a, int toFind)
{
	char	c;
	int		i;

	i = 0;
	c = (char) toFind;
	while (a[i] != '\0')
	{
		if (a[i] == c)
			return ((char *)(a + i));
		i++;
	}
	if (c == '\0')
	{
		return ((char *)(a + i));
	}
	return (0);
}

char	*read_chunk_and_append(int fd, char *rem, char *temp, ssize_t *bytes)
{
	*bytes = read(fd, temp, BUFFER_SIZE);
	if (*bytes <= 0)
		return (rem);
	temp[*bytes] = '\0';
	return (append_new_buffer(rem, temp));
}

int	free_temp(char *rem, char *temp)
{
	if (!rem)
	{
		free(temp);
		return (1);
	}
	return (0);
}

void	ft_safe_free(char **rem)
{
	if (*rem && rem)
	{
		free(*rem);
		*rem = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*rem;
	char		*temp;
	char		*line;
	ssize_t		bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	if (!rem)
		rem = ft_strdup("");
	bytes = 1;
	while (!ft_strchr(rem, '\n') && bytes > 0)
	{
		rem = read_chunk_and_append(fd, rem, temp, &bytes);
		if (free_temp(rem, temp))
			return (NULL);
	}
	free(temp);
	if (!rem || !*rem)
		return (ft_safe_free(&rem), NULL);
	line = extract_line(rem);
	rem = update_rem(rem);
	return (line);
}
