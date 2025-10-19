/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:13:27 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/19 10:41:13 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token **head, t_token **tail, t_token *new)
{
	if (!new)
		return ;
	if (*head == NULL)
		*head = new;
	else
		(*tail)->next = new;
	*tail = new;
}

t_token *tokenization(char *input)
{
	char *word;
	t_token_helper t;
	//init helper
	while (input[end])
	{
		if (input[end] == ' ')
		{
			if (end > start)
			{
				t->word = ft_substr(input, start, end - start);
				add_token(&head, &tail, new_token(t->word));
			}
			start = end + 1;
		}
		end++;
	}
	if (end > start)
	{
		t->word = ft_substr(input, start, end - start);
		add_token(&head, &tail, new_token(t->word));
	}

	return (head);
}
