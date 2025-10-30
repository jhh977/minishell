/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:12 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/29 14:31:11 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void append_reset(t_token_helper *t, char *input)
{
	if(t->end > t->start && !quotes_check(*t))
	{
		append_word(t, input);
		t->start = t->end + 1;
	}
}