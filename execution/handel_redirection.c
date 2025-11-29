/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:49 by aawad             #+#    #+#             */
/*   Updated: 2025/11/29 16:24:29 by marvin           ###   ########.fr       */
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

/* NEW: Handle input redirections */
static int	handle_input_redirs(t_redir *redir_in)
{
	t_redir	*cur;

	cur = redir_in;
	while (cur)
	{
		if (cur->type == REDIR_IN && handle_redir_in(cur->filename) < 0)
			return (-1);
		if (cur->type == REDIR_HEREDOC
			&& handle_redir_heredoc(cur->filename) < 0)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

/* NEW: Handle output redirections */
static int	handle_output_redirs(t_redir *redir_out)
{
	t_redir	*cur;

	cur = redir_out;
	while (cur)
	{
		if (cur->type == REDIR_OUT && handle_redir_out(cur->filename) < 0)
			return (-1);
		if (cur->type == REDIR_APPEND && handle_redir_append(cur->filename) < 0)
			return (-1);
		cur = cur->next;
	}
	return (0);
}

/* UPDATED: Now takes t_cmd instead of t_redir */
int	handle_redirections(t_cmd *cmd)
{
	if (!cmd)
		return (0);
	
	/* Handle input redirections first */
	if (handle_input_redirs(cmd->redir_in) < 0)
		return (-1);
	
	/* Then handle output redirections */
	if (handle_output_redirs(cmd->redir_out) < 0)
		return (-1);
	
	return (0);
}