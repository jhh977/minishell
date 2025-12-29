/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:14:24 by jhh               #+#    #+#             */
/*   Updated: 2025/12/29 17:23:19 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_exit(t_cmd *cmd, char ***envp)
{
		free_cmd_list(cmd);
		free_envp(*envp);
}

void    free_exit_and_pipes(t_cmd *cmd, char ***envp, t_pipe_ctx *ctx, pid_t *pids)
{
    free_exit(cmd, envp);
	free_pipes(ctx->pipes, ctx->num_cmds - 1);
    free(pids);
}

