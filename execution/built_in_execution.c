/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:42 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 15:24:53 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "exit")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset"));
}

void	execute_builtin(t_cmd *cmd, char ***envp)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		built_in_cd(cmd, *envp);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		built_in_export(cmd, envp);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		built_in_unset(cmd, envp);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		built_in_exit(cmd);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		built_in_pwd();
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		built_in_echo(cmd);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		built_in_env(*envp);
}
