/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/14 19:04:38 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *a)
{
	int	i;
	int	count;
	int	qt;
	int space;

	i = 0;
	count = 0;
	space = 1;
	qt = 0;
	while(i < ft_strlen(a))
	{
		if (a[i] == ' ')
			if (space == 0)
			{
				space = 1;
				count++;
			}
		else
		
	}
}
