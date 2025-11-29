/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:16:40 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 13:17:34 by aawad            ###   ########.fr       */
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

void	built_in_exit(t_cmd *cmd)
{
	int	exit_code;

	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(g_last_status);
	if (cmd->args[2] != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		g_last_status = 1;
		return ;
	}
	if (!is_numeric(cmd->args[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(cmd->args[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
		exit(255);
	}
	exit_code = ft_atoi(cmd->args[1]);
	exit(exit_code % 256);
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
