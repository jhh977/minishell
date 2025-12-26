/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_single_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:18:23 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 15:59:47 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *name, char **envp)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (ft_strdup(envp[i] + len + 1));
		i++;
	}
	return (NULL);
}

void	exec_child_process(t_cmd *cmd, char ***envp)
{
	char	*path;

	setup_child_signals();
	if (handle_redirections(cmd) < 0)
	{
		if (g_last_status != 130)
			g_last_status = 1;
		exit(g_last_status);
	}
	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit(127);
	}
	execve(path, cmd->args, *envp);
	perror("execve");
	free(path);
	exit(126);
}

static void	handle_builtin_cmd(t_cmd *cmd, char ***envp)
{
	int	*saved;

	saved = save_std_fds();
	if (!saved)
	{
		g_last_status = 1;
		return ;
	}
	if (handle_redirections(cmd) == 0)
		execute_builtin(cmd, envp);
	else
		g_last_status = 1;
	restore_std_fds(saved);
}

void	execute_single_command(t_cmd *cmd, char ***envp)
{
	pid_t	pid;
	int		status;
	int		sig;

	if (built_in(cmd->args[0]))
	{
		handle_builtin_cmd(cmd, envp);
		return ;
	}
	ignore_signals();
	pid = fork();
	if (pid == 0)
	{
		exec_child_process(cmd, envp);
	}
	else if (pid > 0)
	{
		while (waitpid(pid, &status, 0) == -1)
		{
			if (errno != EINTR)
			{
				perror("waitpid");
				g_last_status = 1;
				break ;
			}
		}
		setup_interactive_signals();
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			g_last_status = 128 + sig;
			if (sig == SIGINT)
				write(1, "\n", 1);
			else if (sig == SIGQUIT)
				write(2, "Quit (core dumped)\n", 20);
		}
	}
	else
	{
		perror("fork");
		g_last_status = 1;
	}
}
