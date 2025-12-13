/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:49 by aawad             #+#    #+#             */
/*   Updated: 2025/12/02 15:55:00 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_fd(char *file, int flags, int mode)
{
	int	fd;

	fd = open(file, flags, mode);
	if (fd < 0)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

int	dup_and_close(int fd, int target)
{
	if (dup2(fd, target) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_input_redirs(t_cmd *cmd)
{
	if (!cmd->redir_in.filename)
		return (0);
	
	if (cmd->redir_in.type == REDIR_IN)
		return (handle_redir_in(cmd->redir_in.filename));
	else if (cmd->redir_in.type == REDIR_HEREDOC)
		return (handle_redir_heredoc(cmd->redir_in.filename));
	
	return (0);
}

static int	handle_output_redirs(t_cmd *cmd)
{
	if (!cmd->redir_out.filename)
		return (0);
	
	if (cmd->redir_out.type == REDIR_OUT)
		return (handle_redir_out(cmd->redir_out.filename));
	else if (cmd->redir_out.type == REDIR_APPEND)
		return (handle_redir_append(cmd->redir_out.filename));
	
	return (0);
}

int	handle_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	if (handle_input_redirs(cmd) < 0)
		return (-1);
	if (handle_output_redirs(cmd) < 0)
		return (-1);
	return (0);
}
