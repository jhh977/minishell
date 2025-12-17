/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 18:09:31 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/17 12:58:57 by jhh              ###   ########.fr       */
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
	{
		ft_putstr_error("Error: Pipe must be followed by a command\n");
		return (0);
	}
	if (tok->next->type == PIPE)
	{
		ft_putstr_error("Error: Consecutive pipes\n");
		return (0);
	}
	return (1);
}

int checker(t_token *tok)
{
	if (tok->type == PIPE)
	{
		ft_putstr_error("Pipe at the beginning of the prompt\n");
		return (0);
	}
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
			{
				ft_putstr_error("bash: syntax error near unexpected token `|'\n");
				return (0);
			}
		}
		tok = tok->next;
	}
	return (1);
}
