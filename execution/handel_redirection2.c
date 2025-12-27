/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:39:45 by aawad             #+#    #+#             */
/*   Updated: 2025/12/27 08:39:09 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_output_redir(t_redir *redir, int *last_fd)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_OUT)
		fd = open_fd(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIR_APPEND)
		fd = open_fd(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	if (*last_fd >= 0)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int	handle_output_redirs(t_cmd *cmd)
{
	t_redir	*current;
	int		last_fd;

	if (!cmd->redirs)
		return (0);
	last_fd = -1;
	current = cmd->redirs;
	while (current)
	{
		if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
		{
			if (process_output_redir(current, &last_fd) < 0)
			{
				if (last_fd >= 0)
					close(last_fd);
				return (-1);
			}
		}
		current = current->next;
	}
	if (last_fd >= 0)
		return (dup_and_close(last_fd, STDOUT_FILENO));
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
