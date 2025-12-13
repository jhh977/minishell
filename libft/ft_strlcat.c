/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:35:04 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:19 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	sz;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
		j++;
	sz = j;
	if (size <= i)
		return (size + j);
	j = 0;
	while (src[j] != '\0' && i + j < size -1)
	{
		dest[i + j] = src [j];
		j++;
	}
	if (i + j < size)
		dest[i + j] = '\0';
	return (sz + i);
}
