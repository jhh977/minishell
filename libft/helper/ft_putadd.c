/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:58:26 by jhijazi           #+#    #+#             */
/*   Updated: 2025/08/15 17:00:23 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putadd(void *ptr)
{
	if (ptr == 0)
		return (ft_putstr("(nil)"));
	ft_putstr("0x");
	return (2 + ft_puthex(0, (unsigned long)ptr));
}
