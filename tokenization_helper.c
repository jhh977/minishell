/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 14:01:12 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/31 16:24:30 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_reset(t_token_helper *t, char *input)
{
	if(t->end > t->start && !quotes_check(*t))
	{
		append_word(t, input);
		t->start = t->end + 1;
	}
}


void	add_special_token(t_token_helper *t, char *input)
{
	if (input[t->start] == '|')
		t->type = PIPE;
	else if(input[t->start] == '<')
	{
		if(input[t->start + 1] && input[t->start + 1] == '<')
		{
			t->end++;
			t->type = REDIR_HEREDOC;
		}
		else
			t->type = REDIR_IN;
	}
	else if(input[t->start] == '>')
	{
		if(input[t->start + 1] && input[t->start + 1] == '>')
		{
			t->end++;
			t->type = REDIR_APPEND;
		}
		else
			t->type = REDIR_OUT;
	}
	append_add_token(t, input);
}

void	check_add_special(t_token_helper *t, char *input)
{
	if (end_of_word(input[t->end]) && input[t->end] != ' ')
	{
		t->start = t->end;
		t->end++;
		add_special_token(t, input);
		t->end--;
	}	
}	
