/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/03 11:18:58 by jihad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	end_of_word(char c)
{
	if (c)
	{	
		if (c == ' ' || c == '|' ||
			c == '<' || c == '>')
			return (1);
	}
	return (0);
}

void	check_word(t_token_helper *t, char *input)
{
	if (quotes_check(*t) || input[t->end] == '\'' || input[t->end] == '\"')
	{
		tokenize_quotes(t, input);
	}
	else if (end_of_word(input[t->end]) && !quotes_check(*t))
	{
		if (t->end > t->start || (t->word && ft_strlen(t->word) > 0))
		{
			append_add_token(t, input);
		}
		check_add_special(t, input);
		t->start = t->end + 1;
	}
	else if (input[t->end] == '$')
	{
		if (input[t->end + 1] == '?')
			handle_question_mark(t, input);
		else
			var_handler(t, input);
	}
	t->end++;
}

t_token *tokenization(char *input)
{
	t_token_helper t;

	token_helper_init(&t);
	while (input[t.end])
	{
		check_word(&t, input);
	}
	if (t.squote || t.dquote)
	{
		printf("minishell: syntax error: unclosed quote\n");
		free_tokens(t.head);
		return (NULL);
	}
	if (t.end > t.start && input[t.start])
	{
		append_add_token(&t, input);
	}
	else if (t.end == t.start && (t.word && ft_strlen(t.word) > 0))
	{
		printf("testPrint");
		add_token(&t, new_token(&t));
	}
	return (t.head);
}
