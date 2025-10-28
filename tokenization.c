/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/28 19:33:44 by jhijazi          ###   ########.fr       */
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

void	add_token_main(t_token_helper *t, char *input)
{
	t->word = ft_substr(input, t->start, t->end - t->start);
	add_token(&t->head, &t->tail, new_token(t->word));
}
// add_token(&t->head, &t->tail, new_token(t->word));

int	end_of_word(t_token_helper *t, char *input)
{
	if (input[t->end] == ' ' || input[t->end] == '|' ||
		input[t->end] == '<' || input[t->end] == '>')
		return (1);
	return (0);
}

t_token *tokenization(char *input)
{
	t_token_helper t;

	token_helper_init(&t);
	while (input[t.end])
	{
		if (quotes_check(t) || input[t.end] == '\'' || input[t.end] == '\"')
			tokenize_quotes(&t, input);
		else if (end_of_word(&t, input) && !quotes_check(t))
		{
			if (t.end > t.start)
			{
				add_token_main(&t, input);
			}
			t.start = t.end + 1;
		}
		t.end++;
	}
	if (t.end > t.start && input[t.start])
	{
		add_token_main(&t, input);
	}
	return (t.head);
}
