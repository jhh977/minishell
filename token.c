/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 08:46:13 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/31 15:03:36 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value)
{
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->value = value;
	tok->type = 0;
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