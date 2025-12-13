/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 09:47:26 by jhijazi           #+#    #+#             */
/*   Updated: 2025/06/27 16:35:31 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calc(int i, const char *nptr)
{
	int	res;

	res = 0;
	while (nptr[i] != '\0' && nptr[i] >= '0' && nptr[i] <= '9')
	{
		res = (res * 10) + (nptr[i] - '0');
		i++;
	}
	return (res);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;

	if (nptr[0] == '\0')
		return (0);
	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	if (nptr[i] >= '0' && nptr[i] <= '9')
		return (sign * ft_calc(i, nptr));
	return (0);
}

// #include <stdio.h>
// #include <stdlib.h>

// int main(){
// 	printf("%d\n", ft_atoi("   \t \n \v  -1"));
// 	printf("%d\n", ft_atoi("-2147483648"));
// 	printf("%d\n", atoi("-2147483648"));
// 	printf("%d\n", ft_atoi("-2147483649"));
// 	printf("%d\n", atoi("-2147483649"));
// 	printf("%d\n", ft_atoi("-----1"));
// 	printf("%d\n", atoi("-----1"));
// 	printf("%d\n", ft_atoi("----1"));
// 	printf("%d\n", atoi("----1"));
// 	printf("%d\n", ft_atoi("\t-+-+-12345"));
// 	printf("%d\n", ft_atoi("5-5"));
// 	printf("%d\n", ft_atoi("55a5"));
// }