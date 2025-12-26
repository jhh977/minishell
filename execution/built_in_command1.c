/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:40 by aawad             #+#    #+#             */
/*   Updated: 2025/12/26 15:34:30 by jhh              ###   ########.fr       */
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
	ft_printf("%s\n", cwd);
	free(cwd);
	g_last_status = 0;
}

//for anthony to check (separated function and replaced printf with ft_printf)
void	echo_helper(t_cmd *cmd, int i)
{
	ft_printf("%s", cmd->args[i]);
	if (cmd->args[i + 1])
		ft_printf(" ");
}

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int	j;
	int	newline;

	j = 1;
	i = 1;
	newline = 1;
	if (cmd->args[i] && cmd->args[i][0] == '-')
	{
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] == '\0' && j > 1)
		{
			newline = 0;
			i++;
		}
	}
	while (cmd->args[i])
	{
		echo_helper(cmd, i);
		i++;
	}
	if (newline)
		ft_printf("\n");
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
		ft_printf("%s\n", envp[i]);
		i++;
	}
	g_last_status = 0;
}
