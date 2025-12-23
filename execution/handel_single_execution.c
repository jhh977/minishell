/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_single_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:18:23 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 14:18:37 by aawad            ###   ########.fr       */
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
		exit(1);
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

	if (built_in(cmd->args[0]))
	{
		handle_builtin_cmd(cmd, envp);
		return ;
	}
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, envp);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_last_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_last_status = 128 + WTERMSIG(status);
	}
	else
	{
		perror("fork");
		g_last_status = 1;
	}
}
