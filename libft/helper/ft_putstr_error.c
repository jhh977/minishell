/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:28:36 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/17 11:49:26 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_error(char *s)
{
	size_t	i;

	if (!s)
		return (ft_putstr_error("(null)"));
	i = 0;
	while (s[i] != '\0')
		i += ft_putchar_error(s[i]);
	return (i);
}
