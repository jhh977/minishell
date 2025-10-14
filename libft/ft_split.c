/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:09:49 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 19:16:34 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	count;
	int	sep;
	int	i;

	count = 0;
	sep = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (sep == 0 && s[i] != c)
		{
			count++;
			sep = 1;
		}
		else if (s[i] == c)
			sep = 0;
		i++;
	}
	return (count);
}

static char	*ft_fill(char const *s, int start, int end)
{
	char	*c;
	int		i;

	i = 0;
	c = malloc ((end - start + 1) * sizeof(char));
	if (!c)
		return (0);
	while (start < end)
	{
		c[i] = s[start];
		i++;
		start++;
	}
	c[i] = '\0';
	return (c);
}

static void	ft_split_fill(char const *s, char c, char **res)
{
	int		sep;
	int		i;
	size_t	j;
	int		len;

	i = 0;
	j = 0;
	sep = -1;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (sep == -1 && s[i] != c)
			sep = i;
		else if ((s[i] == c || i == len) && sep != -1)
		{
			res[j++] = ft_fill(s, sep, i);
			sep = -1;
		}
		i++;
	}
	res[j] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (!s)
		return (0);
	res = malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!res)
		return (0);
	ft_split_fill(s, c, res);
	return (res);
}
