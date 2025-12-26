/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:34:17 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 20:39:54 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_heredoc_filename(void)
{
	static int	heredoc_count = 0;
	char		*count_str;
	char		*filename;
	char		*tmp;

	count_str = ft_itoa(heredoc_count++);
	if (!count_str)
		return (NULL);
	tmp = ft_strjoin("/tmp/.minishell_heredoc_", count_str);
	free(count_str);
	if (!tmp)
		return (NULL);
	filename = ft_strjoin(tmp, ".txt");
	free(tmp);
	return (filename);
}

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;
	int		delim_len;

	delim_len = ft_strlen(delimiter);
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (g_last_status == 130)
				return (-1);
			ft_putstr_fd("minishell: warning: heredoc delimited by EOF\n", 2);
			break ;
		}
		if (ft_strncmp(line, delimiter, delim_len) == 0
			&& line[delim_len] == '\0')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (0);
}

static int	open_heredoc_file(char *filename)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc");
		free(filename);
	}
	return (fd);
}

static int	finalize_heredoc(int fd, char *filename)
{
	int	read_fd;

	setup_interactive_signals();
	close(fd);
	read_fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	if (read_fd < 0)
	{
		perror("heredoc");
		g_last_status = 1;
		return (-1);
	}
	return (read_fd);
}

int	handle_heredoc(char *delimiter)
{
	char	*filename;
	int		fd;

	if (!delimiter)
		return (-1);
	filename = create_heredoc_filename();
	if (!filename)
		return (-1);
	fd = open_heredoc_file(filename);
	if (fd < 0)
		return (-1);
	setup_heredoc_signals();
	if (read_heredoc_lines(fd, delimiter) < 0)
	{
		close(fd);
		unlink(filename);
		free(filename);
		setup_interactive_signals();
		return (-1);
	}
	return (finalize_heredoc(fd, filename));
}
