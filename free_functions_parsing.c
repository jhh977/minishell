/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions_parsing.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:54:30 by jhh               #+#    #+#             */
/*   Updated: 2025/12/23 14:33:06 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_args(char **args, int arg_count)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (i < arg_count)
	{
		if (args[i])
			free(args[i]);
		i++;
	}
	free(args);
}

static void	free_redirs(t_cmd *cmd)
{
	if(!cmd)
		return ;
	if (cmd->redir_in.filename)
		free(cmd->redir_in.filename);
	if (cmd->redir_out.filename)
		free(cmd->redir_out.filename);
}

static void	close_pipe_fds(t_cmd *cmd)
{
	if (cmd->pipe_fd[0] != -1)
		close(cmd->pipe_fd[0]);
	if (cmd->pipe_fd[1] != -1)
		close(cmd->pipe_fd[1]);
}

static void	free_redirs_list(t_cmd *cmd)
{
	t_redir	*current;
	t_redir	*next;

	if (!cmd)
		return ;
	current = cmd->redirs;
	while (current)
	{
		next = current->next;
		if (current->filename)
			free(current->filename);
		free(current);
		current = next;
	}
	cmd->redirs = NULL;
}

void	free_cmd_list(t_cmd *cmd_list)
{
	t_cmd	*current;
	t_cmd	*next;

	current = cmd_list;
	while (current)
	{
		next = current->next;
		free_args(current->args, current->arg_count);
		free_redirs(current);
		close_pipe_fds(current);
		free_redirs_list(current);
		free(current);
		current = next;
	}
}
