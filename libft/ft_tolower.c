/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:50:55 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:43 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_tolower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%c\n", ft_tolower('a'));
// 	printf("%c\n", ft_tolower('A'));
// 	printf("%c\n", ft_tolower('2'));
// 	printf("%c\n", ft_tolower(' '));
// }