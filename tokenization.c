/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/19 17:47:27 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_token_helper *t, t_token *new)
{
	if (!new)
		return ;
	if (t->head == NULL)
		t->head = new;
	else
		(t->tail)->next = new;
	t->tail = new;
	t->word = "";
	t->type = WORD;
}

void	append_word(t_token_helper *t, char *input)
{
	char	*tempstr;

	tempstr = ft_substr(input, t->start, t->end - t->start);
	t->word = ft_strjoin(t->word, tempstr);
	free(tempstr);
}

void	append_add_token(t_token_helper *t, char *input)
{
	append_word(t, input);
	add_token(t, new_token(t));
}

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

t_token *tokenization(char *input)
{
	t_token_helper t;

	token_helper_init(&t);
	while (input[t.end])
	{
		if (quotes_check(t) || input[t.end] == '\'' || input[t.end] == '\"')
		{
			tokenize_quotes(&t, input);
		}
		else if (end_of_word(input[t.end]) && !quotes_check(t))
		{
			if (t.end > t.start)
			{
				append_add_token(&t, input);
			}
			check_add_special(&t, input);
			t.start = t.end + 1;
		}
		else if (input[t.end] == '$')
		{
			var_handler(&t, input);
			t.start = t.end + 1;
		}
		t.end++;
	}
	if (t.end > t.start && input[t.start])
	{
		append_add_token(&t, input);
	}
	else if (t.end == t.start && ft_strlen(t.word) > 0)
		add_token(&t, new_token(&t));
	return (t.head);
}
