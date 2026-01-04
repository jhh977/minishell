/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_cd_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 13:00:00 by aawad             #+#    #+#             */
/*   Updated: 2026/01/04 13:20:44 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_home_path(char **envp)
{
	char	*home;

	home = get_env_value("HOME", envp);
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
		return (NULL);
	}
	return (home);
}

static char	*handle_tilde_path(char *arg, char **envp)
{
	char	*home;
	char	*path;

	home = get_home_path(envp);
	if (!home)
		return (NULL);
	if (arg[1] == '/')
		path = ft_strjoin(home, arg + 1);
	else
		path = ft_strdup(home);
	free(home);
	return (path);
}

static int	is_tilde_path(char *arg)
{
	if (!arg)
		return (0);
	if (arg[0] == '~' && (arg[1] == '\0' || arg[1] == '/'))
		return (1);
	return (0);
}

char	*get_cd_path(t_cmd *cmd, char **envp)
{
	if (!cmd->args[1])
		return (get_home_path(envp));
	if (is_tilde_path(cmd->args[1]))
		return (handle_tilde_path(cmd->args[1], envp));
	return (ft_strdup(cmd->args[1]));
}

void	built_in_cd(t_cmd *cmd, char **envp)
{
	char	*path;

	path = get_cd_path(cmd, envp);
	if (!path)
	{
		g_last_status = 1;
		return ;
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_last_status = 1;
	}
	else
		g_last_status = 0;
	free(path);
}
