/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 22:30:45 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 16:36:09 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
