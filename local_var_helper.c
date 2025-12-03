/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_var_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:30:24 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/29 22:59:08 by jihad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_name_check(char c)
{
	if ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

void	var_handler(t_token_helper *t, char *input)
{
	char	*vname;
	char	*value;
	char	*temp;

	append_word(t, input);
	if (input[t->end + 1] == '\0')
		return ;
	t->start = t->end + 1;
	t->end = t->start;
	while (input[t->end] && var_name_check(input[t->end]))
		t->end++;
	vname = ft_substr(input, t->start, t->end - t->start);
	value = getenv(vname);
	if (value == NULL)
		value = "";
	temp = ft_strjoin(t->word, value);
	free(t->word);
	t->word = temp;
	free(vname);
	t->end--;
	t->start--;
	t->start = t->end + 1;
}

void	handle_question_mark(t_token_helper *t, char *input)
{
	printf("handle_question_mark: t->word before: %p\n", t->word);
	char	*temp;
	char	*codeval;
	char	*old_word;

	append_word(t, input);
	codeval = ft_itoa(t->execcode);
	old_word = t->word;  // Save the old pointer
	temp = ft_strjoin(t->word, codeval);
	free(old_word); 
	t->word = temp;
	free(codeval);
	// if (t->word)
	// 	free(t->word);
	t->end++;
	t->start = t->end + 1;
	printf("handle_question_mark: t->word after: %p\n", t->word);
	// char	*temp;
	// char	*codeval;
	
	// append_word(t, input);
	// codeval = ft_strdup(str_val);
	// temp = ft_strjoin(t->word, codeval);
	// t->word = temp;
	// t->end++;
	// t->start = t->end + 1;
}
