/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_execute_pipeline.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:03:15 by aawad             #+#    #+#             */
/*   Updated: 2025/12/08 20:03:40 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command_child(t_cmd *cmd, char ***envp,
					int cmd_index, int num_cmds, int **pipes)
{
	char	*path;

	setup_pipe_fds(cmd_index, num_cmds, pipes);
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

void	execute_pipeline(t_cmd *cmd_list, char ***envp)
{
	int		num_cmds;
	int		**pipes;
	pid_t	*pids;
	t_cmd	*current;
	int		i;

	if (!cmd_list || !envp)
		return ;
	num_cmds = count_commands(cmd_list);
	if (num_cmds == 1)
	{
		execute_single_command(cmd_list, envp);
		return ;
	}
	pipes = create_pipes(num_cmds);
	if (!pipes)
	{
		perror("create_pipes");
		return ;
	}
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pids)
	{
		free_pipes(pipes, num_cmds - 1);
		perror("malloc");
		return ;
	}
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
			free(pids);
			free_pipes(pipes, num_cmds - 1);
			g_last_status = 1;
			return ;
		}
		else if (pids[i] == 0)
			execute_command_child(current, envp, i, num_cmds, pipes);
		current = current->next;
		i++;
	}
	close_all_pipes(pipes, num_cmds - 1);
	g_last_status = wait_for_children(pids, num_cmds);
	free(pids);
	free_pipes(pipes, num_cmds - 1);
}

int	is_pipeline(t_cmd *cmd_list)
{
	if (!cmd_list)
		return (0);
	return (cmd_list->next != NULL);
}
