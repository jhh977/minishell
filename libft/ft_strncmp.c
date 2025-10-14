/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:54:37 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:36:28 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// #include <stdio.h>
// int main(){
//         printf("%d \n", ft_strncmp("abc", "abc", 2));
//         printf("%d \n", ft_strncmp("abc", "abc", 3));
//         printf("%d \n", ft_strncmp("abc", "abC", 1));
//         printf("%d \n", ft_strncmp("abc", "abC", 2));
//         printf("%d \n", ft_strncmp("abcd", "abc", 4));
//         printf("%d \n", ft_strncmp("abc", "abcd", 4));
//         printf("%d \n", ft_strncmp("abC", "abc", 3));
// }