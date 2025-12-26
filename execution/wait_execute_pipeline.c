/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execute_pipeline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:03:15 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 22:20:10 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command_child(t_cmd *cmd, char ***envp, t_pipe_ctx *ctx)
{
	char	*path;

	setup_child_signals();
	setup_pipe_fds(ctx->cmd_index, ctx->num_cmds, ctx->pipes);
	if (handle_redirections(cmd) < 0)
		exit(1);
	if (built_in(cmd->args[0]))
	{
		execute_builtin(cmd, envp);
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

static void	handle_fork_error(t_pipe_ctx *ctx, pid_t *pids, int i)
{
	perror("fork");
	close_all_pipes(ctx->pipes, ctx->num_cmds - 1);
	while (--i >= 0)
		waitpid(pids[i], NULL, 0);
	free(pids);
	free_pipes(ctx->pipes, ctx->num_cmds - 1);
	g_last_status = 1;
	setup_interactive_signals();
}

static void	fork_and_execute(t_cmd *cmd_list, pid_t *pids,
				t_pipe_ctx *ctx, char ***envp)
{
	t_cmd	*current;
	int		i;

	ignore_signals();
	current = cmd_list;
	i = -1;
	while (++i < ctx->num_cmds && current)
	{
		pids[i] = fork();
		if (pids[i] < 0)
		{
			handle_fork_error(ctx, pids, i);
			return ;
		}
		else if (pids[i] == 0)
		{
			ctx->cmd_index = i;
			execute_command_child(current, envp, ctx);
		}
		current = current->next;
	}
}

static int	init_pipeline_resources(int num_cmds, int ***pipes, pid_t **pids)
{
	*pipes = create_pipes(num_cmds);
	if (!*pipes)
	{
		perror("create_pipes");
		return (0);
	}
	*pids = malloc(sizeof(pid_t) * num_cmds);
	if (!*pids)
	{
		free_pipes(*pipes, num_cmds - 1);
		perror("malloc");
		return (0);
	}
	return (1);
}

void	execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	int			num_cmds;
	int			**pipes;
	pid_t		*pids;
	t_pipe_ctx	ctx;

	if (!cmd_list || !envp)
		return ;
	num_cmds = count_commands(cmd_list);
	if (num_cmds == 1)
	{
		execute_single_command(cmd_list, envp);
		return ;
	}
	if (!init_pipeline_resources(num_cmds, &pipes, &pids))
		return ;
	ctx = (t_pipe_ctx){0, num_cmds, pipes};
	fork_and_execute(cmd_list, pids, &ctx, envp);
	close_all_pipes(pipes, num_cmds - 1);
	g_last_status = wait_for_children(pids, num_cmds);
	setup_interactive_signals();
	free(pids);
	free_pipes(pipes, num_cmds - 1);
}
