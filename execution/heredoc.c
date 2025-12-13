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


int	handle_heredoc(char *delimiter)
{
	char	*filename;
	int		fd;
	int		read_fd;

	if (!delimiter)
		return (-1);
	filename = create_heredoc_filename();
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		perror("heredoc");
		free(filename);
		return (-1);
	}
	read_heredoc_lines(fd, delimiter);
	close(fd);
	read_fd = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	if (read_fd < 0)
	{
		perror("heredoc");
		return (-1);
	}
	return (read_fd);
}