/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:04:33 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:40 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	ft_getmin(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	size_t	s_len;

	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	if (s_len < start)
		return (0);
	j = 0;
	if (len == 0)
		return (0);
	while (s[start + j] != '\0')
		j++;
	if (j > len)
		return (len);
	return (j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sz;
	char	*pt;

	if (!s)
		return (0);
	i = 0;
	sz = ft_getmin(s, start, len);
	pt = malloc(sz + 1);
	if (!pt)
		return (0);
	while (i < sz)
	{
		pt[i] = s[start + i];
		i++;
	}
	pt[i] = '\0';
	return (pt);
}
