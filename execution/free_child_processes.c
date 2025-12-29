/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:14:24 by jhh               #+#    #+#             */
/*   Updated: 2025/12/29 21:46:04 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_child_pipeline(t_pipe_ctx *ctx, pid_t *pids)
{
	if (ctx && ctx->pipes)
		free_pipes(ctx->pipes, ctx->num_cmds - 1);
	if (pids)
		free(pids);
}
