/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 00:02:07 by marvin            #+#    #+#             */
/*   Updated: 2025/11/18 00:02:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int wait_for_children(pid_t *pids, int num_cmds)
{
    int i;
    int status;
    int last_status;

    last_status = 0;
    i = 0;
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
    
    // Return the exit status of the last command
    return (last_status);
}
static void free_pipeline_resources(int **pipes, int num_pipes, pid_t *pids)
{
    int i;

    if (pipes)
    {
        i = 0;
        while (i < num_pipes)
        {
            free(pipes[i]);
            i++;
        }
        free(pipes);
    }
    
    if (pids)
        free(pids);
}