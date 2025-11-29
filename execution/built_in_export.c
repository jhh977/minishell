/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:50:30 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 14:13:09 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("declare -x %s\n", envp[i]);
		i++;
	}
}

int	find_env_index(char **envp, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	built_in_export(t_cmd *cmd, char ***envp)
{
	int		i;
	char	*equal;

	i = 1;
	if (!cmd->args[i])
	{
		print_export(*envp);
		g_last_status = 0;
		return ;
	}
	while (cmd->args[i])
	{
		equal = ft_strchr(cmd->args[i], '=');
		if (equal)
		{
			*equal = '\0';
			*envp = add_or_update_env(*envp, cmd->args[i], equal + 1);
			*equal = '=';
		}
		else
			*envp = add_or_update_env(*envp, cmd->args[i], "");
		i++;
	}
	g_last_status = 0;
}
