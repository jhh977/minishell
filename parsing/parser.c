/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:56:03 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/26 14:56:33 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(t_cmd *cmd, char *value)
{
	char	**new_args;

	if (cmd->arg_count >= cmd->arg_cap)
	{
		cmd->arg_cap *= 2;
		new_args = ft_realloc(cmd->args, sizeof(char *) * cmd->arg_cap);
		if (!new_args)
		{
			ft_putstr_error("Error: Failed to create args array\n");
			return ;
		}
		cmd->args = new_args;
	}
	cmd->args[cmd->arg_count] = ft_strdup(value);
	if (!cmd->args[cmd->arg_count])
	{
		ft_putstr_error("Error: Failed to set Args new value\n");
		return ;
	}
	cmd->arg_count++;
	cmd->args[cmd->arg_count] = NULL;
}

static int	check_parse_helper(t_cmd *cmd, t_token *tokens)
{
	if (!handle_redir(&tokens, cmd))
	{
		free_cmd_list(cmd);
		return (1);
	}
	return (0);
}

t_cmd	*check_parse(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd;

	if (!tokens || !checker(tokens))
		return (NULL);
	cmd_list = NULL;
	while (tokens != NULL)
	{
		cmd = create_cmd();
		while (tokens && tokens->type != PIPE)
		{
			if (is_redir(tokens))
			{
				if (check_parse_helper(cmd, tokens))
					return (cmd_list);
			}
			else if (tokens->type == WORD)
				add_arg(cmd, tokens->value);
			tokens = tokens->next;
		}
		add_cmd_to_list(&cmd_list, cmd);
		if (tokens && tokens->type == PIPE)
			tokens = tokens->next;
	}
	return (cmd_list);
}
