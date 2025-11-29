/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipline_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:53:20 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 12:53:20 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_commands(t_cmd *cmd_list)
{
	int		count;
	t_cmd	*current;

	count = 0;
	current = cmd_list;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	**create_pipes(int num_cmds)
{
	int	**pipes;
	int	i;

	if (num_cmds <= 1)
		return (NULL);
	pipes = malloc(sizeof(int *) * (num_cmds - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < num_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i] || pipe(pipes[i]) < 0)
		{
			perror("pipe");
			while (i >= 0)
				free(pipes[i--]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

static void	close_all_pipes(int **pipes, int num_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	free_pipes(int **pipes, int num_pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = 0;
	while (i < num_pipes)
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

static void	setup_pipe_fds(int cmd_index, int num_cmds, int **pipes)
{
	if (num_cmds <= 1 || !pipes)
		return ;
	if (cmd_index == 0)
		dup2(pipes[0][1], STDOUT_FILENO);
	else if (cmd_index == num_cmds - 1)
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
	else
	{
		dup2(pipes[cmd_index - 1][0], STDIN_FILENO);
		dup2(pipes[cmd_index][1], STDOUT_FILENO);
	}
	close_all_pipes(pipes, num_cmds - 1);
}
