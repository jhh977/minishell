/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipline_execute.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 11:15:57 by aawad             #+#    #+#             */
/*   Updated: 2025/12/08 20:03:47 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int wait_for_children(pid_t *pids, int num_cmds)
{
    int i;
    int status;
    int last_status = 0;

    for (i = 0; i < num_cmds; i++)
    {
        while (waitpid(pids[i], &status, 0) == -1)
        {
            if (errno != EINTR)
            {
                perror("waitpid");
                last_status = 1;
                break;
            }
        }
        if (WIFEXITED(status))
            last_status = WEXITSTATUS(status);
        else if (WIFSIGNALED(status))
            last_status = 128 + WTERMSIG(status);
    }
    return last_status;
}

// static void	free_pipeline_resources(int **pipes, int num_pipes, pid_t *pids)
// {
// 	int	i;

// 	i = 0;
// 	if (pipes != NULL)
// 	{
// 		while (i < num_pipes)
// 		{
// 			free(pipes[i]);
// 			i++;
// 		}
// 		free(pipes);
// 	}
// 	if (pids != NULL)
// 		free(pids);
// }
