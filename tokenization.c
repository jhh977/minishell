/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/29 17:57:53 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_token(t_token **head, t_token **tail, t_token *new)
{
	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
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
	add_token(&t->head, &t->tail, new_token(t->word));
	t->word = "";
}
// add_token(&t->head, &t->tail, new_token(t->word));

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
			append_reset(&t, input);
			tokenize_quotes(&t, input);
		}
		else if (end_of_word(input[t.end]) && !quotes_check(t))
		{
			if (t.end > t.start)
			{
				append_add_token(&t, input);
			}
			t.start = t.end + 1;
		}
		t.end++;
	}
	if (t.end > t.start && input[t.start])
	{
		append_add_token(&t, input);
	}
	return (t.head);
}
