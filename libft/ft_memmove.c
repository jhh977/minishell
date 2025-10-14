/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:09:21 by marvin            #+#    #+#             */
/*   Updated: 2025/06/27 16:35:55 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, unsigned long n)
{
	unsigned long			i;
	unsigned char			*d;
	const unsigned char		*s;

	if (dest == src || n == 0)
		return (dest);
	d = (unsigned char *) dest;
	s = (const unsigned char *) src;
	if (d > s)
	{
		i = n;
		while (i-- > 0)
			d[i] = s[i];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dest);
}

// #include <stdio.h>
// int main()
// {
// 	char a[] = "abcdef";
// 	ft_memmove(a, a+2, 4);
// 	printf("%s", a);
// 	return 0;

// }