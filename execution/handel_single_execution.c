/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_single_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:18:23 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 20:43:05 by aawad            ###   ########.fr       */
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
