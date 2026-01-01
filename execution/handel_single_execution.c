/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_single_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:18:23 by aawad             #+#    #+#             */
/*   Updated: 2026/01/01 18:12:01 by aawad            ###   ########.fr       */
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

static void	handle_command_not_found(t_cmd *cmd, char ***envp)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd->args[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	free_exit(cmd, envp);
	exit(127);
}

static void	execute_command(t_cmd *cmd, char ***envp, char *path)
{
	execve(path, cmd->args, *envp);
	free_exit(cmd, envp);
	perror("execve");
	free(path);
	exit(126);
}

void	exec_child_process(t_cmd *cmd, char ***envp)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(0);
	setup_child_signals();
	if (handle_redirections(cmd) < 0)
	{
		if (g_last_status != 130)
			g_last_status = 1;
		free_exit(cmd, envp);
		exit(g_last_status);
	}
	path = find_path(cmd->args[0], *envp);
	if (!path)
		handle_command_not_found(cmd, envp);
	execute_command(cmd, envp, path);
}
