/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:35:16 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:35 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *a, int toFind)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	j = -1;
	c = (char) toFind;
	while (a[i] != '\0')
	{
		if (a[i] == c)
			j = i;
		i++;
	}
	if (c == '\0')
	{
		return ((char *)(a + i));
	}
	if (j == -1)
		return (0);
	return ((char *)(a + j));
}
