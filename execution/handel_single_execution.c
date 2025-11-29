/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_single_execution.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:18:23 by aawad             #+#    #+#             */
/*   Updated: 2025/11/29 11:16:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_builtin_cmd(t_cmd *cmd, char ***envp)
{
	int	*saved;

	saved = save_std_fds();
	if (!saved)
	{
		g_last_status = 1;
		return ;
	}
	if (handle_redirections(cmd->redirections) == 0)
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
