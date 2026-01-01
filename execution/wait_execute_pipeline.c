/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execute_pipeline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:03:15 by aawad             #+#    #+#             */
/*   Updated: 2026/01/01 18:15:50 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			execute_command_child(current, envp, ctx, pids);
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
