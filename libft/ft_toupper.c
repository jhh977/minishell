/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:36:14 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:46 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_toupper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

// #include <stdio.h>
// int main()
// {
// 	printf("%c\n", ft_toupper('a'));
// 	printf("%c\n", ft_toupper('A'));
// 	printf("%c\n", ft_toupper('2'));
// 	printf("%c\n", ft_toupper(' '));
// }