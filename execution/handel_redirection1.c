/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:49 by aawad             #+#    #+#             */
/*   Updated: 2025/12/27 08:38:56 by aawad            ###   ########.fr       */
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

static int	process_input_redir(t_redir *redir, int *last_fd)
{
	int	fd;

	fd = -1;
	if (redir->type == REDIR_IN)
		fd = open_fd(redir->filename, O_RDONLY, 0);
	else if (redir->type == REDIR_HEREDOC)
		fd = handle_heredoc(redir->filename);
	if (fd < 0)
		return (-1);
	if (*last_fd >= 0)
		close(*last_fd);
	*last_fd = fd;
	return (0);
}

int	handle_input_redirs(t_cmd *cmd)
{
	t_redir	*current;
	int		last_fd;

	if (!cmd->redirs)
		return (0);
	last_fd = -1;
	current = cmd->redirs;
	while (current)
	{
		if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
		{
			if (process_input_redir(current, &last_fd) < 0)
			{
				if (last_fd >= 0)
					close(last_fd);
				return (-1);
			}
		}
		current = current->next;
	}
	if (last_fd >= 0)
		return (dup_and_close(last_fd, STDIN_FILENO));
	return (0);
}