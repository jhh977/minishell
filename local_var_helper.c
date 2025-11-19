/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:30:24 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/19 17:49:41 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_name_check(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

void	var_handler(t_token_helper *t, char *input)
{
	char	*vname;
	char	*value;
	char	*temp;

	append_word(t, input);
	if (input[t->end + 1] == '\0')
		return ;
	t->start = t->end + 1;
	t->end = t->start;
	while (input[t->end] && var_name_check(input[t->end]))
		t->end++;
	vname = ft_substr(input, t->start, t->end - t->start);
	value = getenv(vname);
	if (value == NULL)
		value = "";
	temp = ft_strjoin(t->word, value);
	t->word = temp;

	free(vname);
	t->end--;
	t->start--;
}
