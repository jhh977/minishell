/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:15:57 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 11:15:57 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_children(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < num_cmds)
	{
		if (waitpid(pids[i], &status, 0) > 0)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

static void	free_pipeline_resources(int **pipes, int num_pipes, pid_t *pids)
{
	int	i;

	i = 0;
	if (pipes != NULL)
	{
		while (i < num_pipes)
		{
			free(pipes[i]);
			i++;
		}
		free(pipes);
	}
	if (pids != NULL)
		free(pids);
}
