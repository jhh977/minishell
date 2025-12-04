/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:09:31 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/04 19:14:08 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redir(t_token *tok)
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
	if (tok->next->type == PIPE)
		return (0);
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
				return (0);
		}
		tok = tok->next;
	}
	return (1);
}