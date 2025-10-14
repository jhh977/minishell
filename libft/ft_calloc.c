/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 11:01:42 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 17:09:59 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	void	*pt;

	i = nmemb * size;
	if (size && i / size != nmemb)
		return (0);
	pt = malloc(i);
	if (!pt)
		return (0);
	ft_bzero(pt, i);
	return (pt);
}
