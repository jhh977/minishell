/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:49:26 by jihad             #+#    #+#             */
/*   Updated: 2025/12/06 22:06:02 by jihad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	create_redir(t_token_type type, char *filename)
{
	t_redir	redir;

	redir.type = type;
	redir.filename = ft_strdup(filename);	return (redir);
}

static void	add_redir_to_cmd(t_cmd *cmd, t_redir redir)
{
	if (redir.type == REDIR_IN || redir.type == REDIR_HEREDOC)
	{
		if (cmd->redir_in.filename)
			free(cmd->redir_in.filename);
		cmd->redir_in = redir;
	}
	else if (redir.type == REDIR_OUT || redir.type == REDIR_APPEND)
	{
		if (cmd->redir_out.filename)
			free(cmd->redir_out.filename);
		cmd->redir_out = redir;
	}
}

void	handle_redir(t_token **token, t_cmd *cmd)
{
	t_redir	redir;

	if ((*token)->type == REDIR_IN)
		redir = create_redir(REDIR_IN, (*token)->next->value);
	else if ((*token)->type == REDIR_OUT)
		redir = create_redir(REDIR_OUT, (*token)->next->value);
	else if ((*token)->type == REDIR_APPEND)
		redir = create_redir(REDIR_APPEND, (*token)->next->value);
	else if ((*token)->type == REDIR_HEREDOC)
		redir = create_redir(REDIR_HEREDOC, (*token)->next->value);
	else
		return ;
	add_redir_to_cmd(cmd, redir);
	*token = (*token)->next->next;
}
