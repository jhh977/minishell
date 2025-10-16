/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/15 17:10:54 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_space(int *space, int qt, char c)
{
	if (c == ' ' && qt == 0)
	{
		if (*space == 0)
		{
			*space = 1;
			return (1);
		}
	}
	else
		*space = 0;
	return (0);
}
static int	check_quotation(int *qt, char c)
{
	if (c == '\'' || c == '\"')
	{
		if (*qt == 0)
		{
			*qt = c;
			return (1);
		}
		else if (*qt == c)
		{
			*qt = 0;
			return (1);
		}
	}
	return (0);
}

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
		count += check_space(&space, qt, a[i]);
		check_quotation(&qt, a[i]);
		i++;
	}
	return (count);
}
