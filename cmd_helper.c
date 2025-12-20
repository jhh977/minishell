/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:56:46 by jihad             #+#    #+#             */
/*   Updated: 2025/12/20 17:01:53 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg_cap = 10;
	cmd->args = malloc(sizeof(char *) * cmd->arg_cap);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->arg_count = 0;
	cmd->redir_in.filename = NULL;
	cmd->redir_out.filename = NULL;
	cmd->next = NULL;
	cmd->prev = NULL;
	cmd->pipe_fd[0] = -1;
	cmd->pipe_fd[1] = -1;
	cmd->redirs = NULL;
	return (cmd);
}

void	add_cmd_to_list(t_cmd **list, t_cmd *new_cmd)
{
	t_cmd	*last;

	if (*list == NULL)
		*list = new_cmd;
	else
	{
		last = *list;
		while (last->next)
			last = last->next;
		last->next = new_cmd;
		new_cmd->prev = last;
	}
	// No need to reset anything
}
