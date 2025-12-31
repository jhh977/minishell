/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_child_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 17:14:24 by jhh               #+#    #+#             */
/*   Updated: 2025/12/31 17:22:48 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


 void free_exit(t_cmd *cmd , char ***envp)
 {
	free_cmd_list(cmd);
	free_envp(*envp);
 }
 
 void	free_child_pipeline(t_cmd *cmd, char ***envp, t_pipe_ctx *ctx, pid_t *pids)
{
	free_exit(cmd, envp);
	if (ctx && ctx->pipes)
		free_pipes(ctx->pipes, ctx->num_cmds - 1);
	if (pids)
		free(pids);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
