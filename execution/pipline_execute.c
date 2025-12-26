/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipline_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:15:57 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 22:20:26 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_child_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	wait_for_children(pid_t *pids, int num_cmds)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	while (i < num_cmds)
	{
		while (waitpid(pids[i], &status, 0) == -1)
		{
			if (errno != EINTR)
			{
				perror("waitpid");
				last_status = 1;
				break ;
			}
		}
		last_status = handle_child_status(status);
		i++;
	}
	return (last_status);
}

int	is_pipeline(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (0);
	return (cmd_list->next != NULL);
}
