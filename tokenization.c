/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/14 19:49:02 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_space(int *space, int qt, char *a)
{
	if (a[i] == ' ' && qt == 0)
		if (space == 0)
		{
			*space = 1;
			return (1);
		}
		return (0);
}
int	check_quotations(int *qt, char *a)
{
	
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
		count += check_space(&space, qt, a);
		count += check_
	}
}
