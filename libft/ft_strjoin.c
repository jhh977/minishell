/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 12:51:05 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/27 18:01:34 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_concat_string(char *res, const char *str1, const char *str2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str1[i] != '\0')
	{
		res[j] = str1[i];
		i++;
		j++;
	}
	i = 0;
	while (str2[i] != '\0')
	{
		res[j] = str2[i];
		i++;
		j++;
	}
	res[j] = '\0';
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	int		length;
	char	*res;

	if (!str1 && !str2)
		return (ft_strdup(""));
	if (!str1)
		return (ft_strdup(str2));
	if (!str2)
		return (ft_strdup(str1));
	length = ft_strlen(str1) + ft_strlen(str2);
	res = malloc((length + 1) * sizeof(char));
	if (!res)
		return (0);
	ft_concat_string(res, str1, str2);
	return (res);
}

// #include <stdio.h>
// int main()
// {
//  char *str1 = "zzzzzzzzzzzzzz";
//  char *str2 = "aaaaaaaaaa";
//  char *result = ft_strjoin(str1, str2);
//  printf("%s\n", result);
//  free(result);
//  return 0;
// }