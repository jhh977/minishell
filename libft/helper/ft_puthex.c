/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:19:13 by jhijazi           #+#    #+#             */
/*   Updated: 2025/08/15 17:00:31 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_puthex(int type, unsigned long a)
{
	char	*hex;
	int		count;

	count = 0;
	if (type == 0)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (a >= 16)
		count += ft_puthex(type, a / 16);
	ft_putchar(hex[a % 16]);
	return (count + 1);
}
