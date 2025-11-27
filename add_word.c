/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:00:54 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/27 18:02:20 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_token_helper *t, t_token *new)
{
	if (!new)
		return ;
	if (t->head == NULL)
		t->head = new;
	else
		(t->tail)->next = new;
	t->tail = new;
	t->word = NULL;
	t->type = WORD;
}

void	append_word(t_token_helper *t, char *input)
{
	char	*tempstr;
	char	*newword;

	if (t->word)
	tempstr = ft_substr(input, t->start, t->end - t->start);
	newword = ft_strjoin(t->word, tempstr);
	free (t->word);
	free(tempstr);
	t->word = newword;
}

void	append_add_token(t_token_helper *t, char *input)
{
	append_word(t, input);
	add_token(t, new_token(t));
}
