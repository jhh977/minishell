/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 19:05:42 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/28 10:00:40 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t size)
{
	size_t				i;
	const unsigned char	*p;

	p = (const unsigned char *) ptr;
	i = 0;
	while (i < size)
	{
		if (p[i] == (unsigned char) value)
			return ((void *)(p + i));
		i++;
	}
	return (0);
}
