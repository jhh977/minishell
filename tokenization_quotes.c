/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:42:21 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/20 18:13:34 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_quotes(t_token_helper *t, char *input)
{
	if (input[t->end] == '\'' && t->dquote == 0)
	{
		if (t->end > 0 && input[t->end - 1] == '\\')
			return ;
		else
			t->squote = (t->squote + 1) % 2;
	}
	if (input[t->end] == '\"' && t->squote == 0)
	{
		if (t->end > 0 && input[t->end - 1] == '\\')
			return ;
		else
			t->dquote = (t->dquote + 1) % 2;
	}
}

int	quotes_check(t_token_helper t)
{
	if (t.squote || t.dquote)
		return (1);
	return (0);
}

static int	compatibility(t_token_helper t, char *input)
{
	if (t.squote && input[t.end] == '\'')
		return (1);
	if (t.dquote && input[t.end] == '\"')
		return (1);
	return (0);
}

static void	end_of_quote(t_token_helper *t, char *input)
{
	int	spaces;

	spaces = 0;
	while (input[t->end - spaces - 1] == ' ')
		spaces++;
	t->end -= spaces;
	if (end_of_word(input[t->end + 1]) || !input[t->end + 1])
		append_add_token(t, input);
	else
		append_word(t, input);
	t->end += spaces;
	spaces = 0;
	t->start = t->end + 1;
}

void	tokenize_quotes(t_token_helper *t, char *input)
{
	append_reset(t, input);
	toggle_quotes(t, input);
	if (!quotes_check(*t))
	{
		if (input[t->end] == '\'' || input[t->end] == '\"')
		{
			end_of_quote(t, input);
		}
	}
	else
	{
		if (input[t->end] == '$' && t->dquote)
			var_handler(t, input);
		if (t->end == t->start
			&& (compatibility(*t, input) || input[t->end] == ' '))
			t->start ++;
	}	
}
