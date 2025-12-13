/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:09:31 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/06 14:39:11 by jihad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir(t_token *tok)
{
	if (!tok)
		return (0);
	return (
		tok->type == REDIR_IN
		|| tok->type == REDIR_OUT
		|| tok->type == REDIR_APPEND
		|| tok->type == REDIR_HEREDOC);
}

static int check_pipe(t_token *tok)
{
	if (!tok->next)
		return (0);
	//print error
	if (tok->next->type == PIPE)
		return (0);
	//print error
	return (1);
}

int checker(t_token *tok)
{
	if (tok->type == PIPE)
		return (0);
	while (tok)
	{
		if (tok->type == PIPE)
		{
			if (!check_pipe(tok))
				return (0);
		}
		if (is_redir(tok))
		{
			if (tok->next && (is_redir(tok->next) || tok->next->type == PIPE))
				//print error
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}