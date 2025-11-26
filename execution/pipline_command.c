/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oipline_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 18:49:37 by marvin            #+#    #+#             */
/*   Updated: 2025/11/15 18:49:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_command(t_cmd *cmd_list)
{
    int count;
    t_cmd current;
    count = 0;
    while (current)
    {
        count++;
        current = current->next;
    }
    return(count);
}

int create_pipe(int num_cmds)
{
    int **pipes;
    int i;

    if(num_cmds <= 1)
        return (NULL);
    
    pipes = malloc(sizeof(num_cmds - 1) * (int *));
    if(!pipes)
        return (NULL);
    i = 0;
    while (i < num_cmds - 1)
    {
        pipes[i] = malloc(sizeof(int) * 2);
        if(pipe(pipes[i]) < 0)
        {
            perror("pipe");
            while(i>=0)
            {
                free(pipes[i]);
                i--;
            }
            return(NULL);
        }
        i++;
    }
    return(pipes);
}

void close_all_pipes(int **pipes,int num_pipes)
{
    int i;
    if(!pipes)
        return ;
    i = 0;
    while(i<num_pipes)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
        i++;
    }
}
void setup_pipe_fds(int cmd_index , int num_cmds , int  **pipes)
{
    if(cmd_index == 0  && num_cmds >1)
    {
        dup2(pipes[0][1] , STDOUT_FILENO);
    }
    else if(cmd_index == num_cmds - 1 && num_cmds > 1)
    {
        dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
    }
    else if(cmd_index > 0 && cmd_index < num_cmds -1 )
    {
        dup2(pipes[cmd_index - 1][0],STDIN_FILENO);
        dup2(pipes[cmd_index][1],STDOUT_FILENO);
    }
    close_all_pipes(pipes,num_cmds - 1);
}
static void execute_command_child(t_cmd *cmd, char ***envp, 
                                   int cmd_index, int num_cmds, int **pipes)
{
    char *path;

    setup_pipe_fds(cmd_index, num_cmds, pipes);
    
    if (handle_redirections(cmd->redirections) < 0)
        exit(1);
    
    if (built_in(cmd->args[0]))
    {
        execute_builtin(cmd, envp);
        exit(0); 
    }
    
    path = find_path(cmd->args[0], *envp);
    if (!path)
    {
        fprintf(stderr, "minishell: %s: command not found\n", cmd->args[0]);
        exit(127);
    }
    
    execve(path, cmd->args, *envp);
    
    perror("execve");
    free(path);
    exit(1);
}
void execute_pipeline(t_cmd *cmd_list, char ***envp)
{
    int num_cmds;
    int **pipes;
    pid_t *pids;
    t_cmd *current;
    int i;
    int exit_status;

    if (!cmd_list)
        return;
    
    // Count commands in pipeline
    num_cmds = count_commands(cmd_list);
    
    // Single command - use simple execution
    if (num_cmds == 1)
    {
        execute_single_command(cmd_list, envp);
        return;
    }
    
    // Create pipes
    pipes = create_pipes(num_cmds);
    if (!pipes)
    {
        perror("create_pipes");
        return;
    }
    
    // Allocate array for child PIDs
    pids = malloc(sizeof(pid_t) * num_cmds);
    if (!pids)
    {
        free_pipeline_resources(pipes, num_cmds - 1, NULL);
        perror("malloc");
        return;
    }
    
    // Fork and execute each command
    current = cmd_list;
    i = 0;
    while (i < num_cmds && current)
    {
        pids[i] = fork();
        
        if (pids[i] < 0)
        {
            perror("fork");
            close_all_pipes(pipes, num_cmds - 1);
            while (--i >= 0)
                waitpid(pids[i], NULL, 0);
            free_pipeline_resources(pipes, num_cmds - 1, pids);
            return;
        }
        else if (pids[i] == 0)
        {
            execute_command_child(current, envp, i, num_cmds, pipes);

            exit(1);
        }

        current = current->next;
        i++;
    }
    
    close_all_pipes(pipes, num_cmds - 1);
    
    exit_status = wait_for_children(pids, num_cmds);

    free_pipeline_resources(pipes, num_cmds - 1, pids);
}
int is_pipeline(t_cmd *cmd_list)
{
    if (!cmd_list)
        return (0);
    return (cmd_list->next != NULL);
}
int is_pipeline(t_cmd *cmd_list)
{
    if (!cmd_list)
        return (0);
    return (cmd_list->next != NULL);
}