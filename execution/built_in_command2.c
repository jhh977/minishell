/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:16:40 by aawad             #+#    #+#             */
/*   Updated: 2026/01/02 16:34:33 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	built_in_exit(t_cmd *cmd, char ***envp,
	t_pipe_ctx *ctx, pid_t *pids)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit_code = g_last_status;
	else if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_last_status = 1;
		return ;
	}
	else if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit_code = 255;
	}
	else
		exit_code = ft_atoi(cmd->args[1]) % 256;
	free_child_pipeline(cmd, envp, ctx, pids);
	exit(exit_code);
}

void	built_in_unset(t_cmd *cmd, char ***envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		*envp = remove_env(*envp, cmd->args[i]);
		i++;
	}
	g_last_status = 0;
}
