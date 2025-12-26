/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:39:45 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 15:18:35 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redir_in(char *file)
{
	int	fd;

	fd = open_fd(file, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	return (dup_and_close(fd, STDIN_FILENO));
}

int	handle_redir_out(char *file)
{
	int	fd;

	fd = open_fd(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	return (dup_and_close(fd, STDOUT_FILENO));
}

int	handle_redir_append(char *file)
{
	int	fd;

	fd = open_fd(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (-1);
	return (dup_and_close(fd, STDOUT_FILENO));
}

int	handle_redir_heredoc(char *delimiter)
{
	int	fd;

	fd = handle_heredoc(delimiter);
	if (fd < 0)
	{
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		g_last_status = 1;
		return (-1);
	}
	close(fd);
	return (0);
}
