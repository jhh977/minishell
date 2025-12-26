/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:00:54 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/26 13:09:47 by jhh              ###   ########.fr       */
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

	tempstr = ft_substr(input, t->start, t->end - t->start);
	newword = ft_strjoin(t->word, tempstr);
	free(tempstr);
	free(t->word);
	t->word = newword;
}

void	append_add_token(t_token_helper *t, char *input)
{
	append_word(t, input);
	add_token(t, new_token(t));
}
