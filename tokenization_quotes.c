/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 12:42:21 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/28 13:41:11 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	toggle_quotes(t_token_helper *t, char *input)
{
	if (input[t->end] == '\'' && t->dquote == 0)
	{
		if(t->end > 0 && input[t->end - 1] == '\\')
			return ;
		else
			t->squote = (t->squote + 1) % 2;
	}
	if (input[t->end] == '\"' && t->squote == 0)
	{
		if(t->end > 0 && input[t->end - 1] == '\\')
			return ;
		else
			t->dquote = (t->dquote + 1) % 2;
	}
	// printf("single: %d double: %d \n", t->squote, t->dquote);
}

int	quotes_check(t_token_helper t)
{
	if (t.squote || t.dquote)
		return (1);
	return (0);
}

int	compatibility(t_token_helper t, char *input)
{
	if (t.squote && input[t.end] == '\'')
		return (1);
	if (t.dquote && input[t.end] == '\"')
		return (1);
	return (0);
}

void tokenize_quotes(t_token_helper *t, char *input)
{
	int	spaces;

	spaces = 0;
	toggle_quotes(t, input);
	if (!quotes_check(*t))
	{
		if(input[t->end] == '\'' || input[t->end] == '\"')
		{
			while (input[t->end - spaces - 1] == ' ')
				spaces++;
			t->end -= spaces;
			add_token_main(t, input);
			t->end += spaces;
			spaces = 0;
			t->start = t->end + 1;
		}
	}
	else
	{
		if(t->end == t->start &&
			(compatibility(*t, input) || input[t->end] == ' '))
			t->start ++;
	}	
}

// int main()
// {
// 	t_token_helper t;
// 	token_helper_init(&t);
// 	printf("s= %d, d= %d\n", t.squote, t.dquote);
// 	toggle_quotes(&t, '\'');
// 	printf("s= %d, d= %d\n", t.squote, t.dquote);
// 	if (quotes_check(t))
// 		printf("there is quotes\n");
// 	else
// 		printf("there is no quotes\n");
// 	toggle_quotes(&t, '\"');
// 	printf("s= %d, d= %d\n", t.squote, t.dquote);
// 	return 0;
// }
