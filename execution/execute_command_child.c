/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 18:15:19 by aawad             #+#    #+#             */
/*   Updated: 2026/01/01 18:16:05 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_empty_cmd(t_cmd *cmd, char ***envp,
	t_pipe_ctx *ctx, pid_t *pids)
{
	if (cmd && handle_redirections(cmd) < 0)
	{
		free_child_pipeline(cmd, envp, ctx, pids);
		exit(1);
	}
	free_child_pipeline(cmd, envp, ctx, pids);
	exit(0);
}

static void	handle_builtin_pipeline(t_cmd *cmd, char ***envp,
	t_pipe_ctx *ctx, pid_t *pids)
{
	execute_builtin(cmd, envp);
	free_child_pipeline(cmd, envp, ctx, pids);
	exit(g_last_status);
}

static void	execute_external_cmd(t_cmd *cmd, char ***envp,
	t_pipe_ctx *ctx, pid_t *pids)
{
	char	*path;

	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		free_child_pipeline(cmd, envp, ctx, pids);
		exit(127);
	}
	execve(path, cmd->args, *envp);
	free_child_pipeline(cmd, envp, ctx, pids);
	perror("execve");
	free(path);
	exit(126);
}

void	execute_command_child(t_cmd *cmd, char ***envp,
	t_pipe_ctx *ctx, pid_t *pids)
{
	setup_child_signals();
	setup_pipe_fds(ctx->cmd_index, ctx->num_cmds, ctx->pipes);
	if (!cmd || !cmd->args || !cmd->args[0])
		handle_empty_cmd(cmd, envp, ctx, pids);
	if (handle_redirections(cmd) < 0)
	{
		free_child_pipeline(cmd, envp, ctx, pids);
		exit(1);
	}
	if (built_in(cmd->args[0]))
		handle_builtin_pipeline(cmd, envp, ctx, pids);
	execute_external_cmd(cmd, envp, ctx, pids);
}
