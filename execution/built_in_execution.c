/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_execution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:42 by aawad             #+#    #+#             */
/*   Updated: 2025/11/08 19:55:01 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	built_in(char *cmd)
{
	return (!ft_strncmp(cmd, "echo", 5)
		||!ft_strncmp(cmd, "pwd", 5)
		||!ft_strncmp(cmd, "cd", 3)
		||!ft_strncmp(cmd, "exit", 5)
		||!ft_strncmp(cmd, "env", 4)
		||!ft_strncmp(cmd, "export", 7)
		||!ft_strncmp(cmd, "unset", 6));
}
// Run cd, export, unset, exit in the parent process (without fork).
// Run pwd, echo, env in child or parent — both are fine.

void	execute_builtin(t_cmd *cmd, char ***envp)
{
	if (ft_strncmp(cmd->args[0], "cd", 3) == 0)
		built_in_cd(cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "export", 7) == 0)
		built_in_export(cmd, envp);
	else if (ft_strncmp (cmd->args[0], "unset", 6) == 0)
		built_in_unset(cmd, envp);
	else if (ft_strncmp(cmd->args[0],"exit", 5) == 0)
		built_in_exit(cmd->args[1]);
	else if (ft_strncmp(cmd->args[0], "pwd", 4) == 0)
		built_in_pwd();
	else if (ft_strncmp(cmd->args[0], "echo", 5) == 0)
		built_in_echo(cmd);
	else if (ft_strncmp(cmd->args[0], "env", 4) == 0)
		built_in_env(envp);
}
