/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:40 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 13:16:27 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		g_last_status = 1;
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
	g_last_status = 0;
}

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int j;
	int	newline;

	j = 1;
	i = 1;
	newline = 1;
	if (cmd->args[i] && cmd->args[i][0] == '-')
	{
		while(cmd->args[i][j] == 'n')
		{
			j++;
		}
		if (cmd->args[i][j] == '\0' && j > 1)
		{
			newline = 0;
			i++;
		}
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	g_last_status = 0;
}

void	built_in_cd(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*home;

	if (cmd->args[1])
		path = cmd->args[1];
	else
	{
		home = get_env_value("HOME", envp);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			g_last_status = 1;
			return ;
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_last_status = 1;
	}
	else
		g_last_status = 0;
	if (!cmd->args[1])
		free(path);
}

void	built_in_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	g_last_status = 0;
}
