/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:00:05 by aawad             #+#    #+#             */
/*   Updated: 2025/11/11 18:41:26 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redir_in(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_out(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_append(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_heredoc(char *delimiter)
{
	char	*temp_file;
	int		fd;

	temp_file = ft_strjoin("/tmp/heredoc_", delimiter);
	if (!temp_file)
		return (-1);
	fd = open(temp_file, O_RDONLY);
	free(temp_file);
	if (fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_redirections(t_redir *redirections)
{
	t_redir	*current;

	current = redirections;
	while (current)
	{
		if (current->type == REDIR_IN)
		{
			if (handle_redir_in(current->filename) < 0)
				return (-1);
		}
		else if (current->type == REDIR_OUT)
		{
			if (handle_redir_out(current->filename) < 0)
				return (-1);
		}
		else if (current->type == REDIR_APPEND)
		{
			if (handle_redir_append(current->filename) < 0)
				return (-1);
		}
		else if (current->type == REDIR_HEREDOC)
		{
			if (handle_redir_heredoc(current->filename) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
