/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 18:56:03 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/06 21:11:17 by jihad            ###   ########.fr       */
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
			return ;
		//handle error
		cmd->args = new_args;
	}
	cmd->args[cmd->arg_count] = ft_strdup(value);
	if (!cmd->args[cmd->arg_count])
		return ;
	//handle error
	cmd->arg_count++;
	cmd->args[cmd->arg_count] = NULL;
}

t_cmd	*check_parse(t_token *tokens)
{
	t_cmd	*cmd_list;
	t_cmd	*cmd;

	if (!checker(tokens))
		return (NULL);
	
	cmd_list = NULL;
	while (tokens != NULL)
	{
		cmd = create_cmd();
		while (tokens && tokens->type != PIPE)
		{
			if (is_redir(tokens))
				handle_redir(&tokens, cmd);
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
