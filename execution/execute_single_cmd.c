/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 20:33:29 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 20:43:11 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_parent_status(int status)
{
	int	sig;

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

static void	wait_for_child(pid_t pid)
{
	int	status;

	while (waitpid(pid, &status, 0) == -1)
	{
		if (errno != EINTR)
		{
			perror("waitpid");
			g_last_status = 1;
			return ;
		}
	}
	handle_parent_status(status);
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

	if (built_in(cmd->args[0]))
	{
		handle_builtin_cmd(cmd, envp);
		return ;
	}
	ignore_signals();
	pid = fork();
	if (pid == 0)
		exec_child_process(cmd, envp);
	else if (pid > 0)
		wait_for_child(pid);
	else
	{
		perror("fork");
		g_last_status = 1;
	}
}
