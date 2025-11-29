/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:49 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:50 by aawad            ###   ########.fr       */
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

int	handle_redirections(t_redir *redir)
{
	t_redir	*cur;

	cur = redir;
	while (cur)
	{
		if (cur->type == REDIR_IN && handle_redir_in(cur->filename) < 0)
			return (-1);
		if (cur->type == REDIR_OUT && handle_redir_out(cur->filename) < 0)
			return (-1);
		if (cur->type == REDIR_APPEND && handle_redir_append(cur->filename) < 0)
			return (-1);
		if (cur->type == REDIR_HEREDOC
			&& handle_redir_heredoc(cur->filename) < 0)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
