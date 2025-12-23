/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 14:49:26 by jihad             #+#    #+#             */
/*   Updated: 2025/12/23 20:14:52 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir	create_redir(t_token_type type, char *filename)
{
	t_redir	redir;

	redir.type = type;
	redir.filename = ft_strdup(filename);	return (redir);
}

static void	add_redir_to_list(t_cmd *cmd, t_redir redir)
{
	t_redir	*new_node;
	t_redir	*current;

	new_node = malloc(sizeof(t_redir));
	if (!new_node)
	{
		ft_putstr_error("Error: Failed to create new node\n");
		return ;
	}
	new_node->type = redir.type;
	new_node->filename = ft_strdup(redir.filename);
	new_node->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = new_node;
	else
	{
		current = cmd->redirs;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
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
	add_redir_to_list(cmd, redir);
}

int	handle_redir(t_token **token, t_cmd *cmd)
{
	t_redir	redir;

	if (!(*token)->next)
	{
		ft_putstr_error("bash: syntax error near unexpected token `newline'\n");
		return (0);
	}
	else if ((*token)->type == REDIR_IN)
		redir = create_redir(REDIR_IN, (*token)->next->value);
	else if ((*token)->type == REDIR_OUT)
		redir = create_redir(REDIR_OUT, (*token)->next->value);
	else if ((*token)->type == REDIR_APPEND)
		redir = create_redir(REDIR_APPEND, (*token)->next->value);
	else if ((*token)->type == REDIR_HEREDOC)
		redir = create_redir(REDIR_HEREDOC, (*token)->next->value);
	else
		return (0);
	add_redir_to_cmd(cmd, redir);
	*token = (*token)->next;
	return (1);
}
