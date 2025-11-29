/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:40:49 by aawad             #+#    #+#             */
/*   Updated: 2025/11/29 11:16:52 by marvin           ###   ########.fr       */
=======
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:00:05 by aawad             #+#    #+#             */
/*   Updated: 2025/11/11 18:41:26 by aawad            ###   ########.fr       */
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

<<<<<<< HEAD
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
=======
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
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

<<<<<<< HEAD
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
=======
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
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
	}
	return (0);
}
