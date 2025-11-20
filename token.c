/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:46:13 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/20 18:13:56 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(t_token_helper *t)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = t->word;
	tok->type = t->type;
	tok->next = NULL;
	return (tok);
}

void	token_helper_init(t_token_helper *t)
{
	t->start = 0;
	t->end = 0;
	t->head = NULL;
	t->tail = NULL;
	t->dquote = 0;
	t->squote = 0;
	t->word = "";
	t->type = WORD;
}
