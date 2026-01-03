/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 00:12:38 by aawad             #+#    #+#             */
/*   Updated: 2026/01/04 00:15:00 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_export_with_value(char *arg, char ***envp)
{
	char	*equal;
	char	*key;

	equal = ft_strchr(arg, '=');
	key = ft_substr(arg, 0, equal - arg);
	if (!key)
		return ;
	*envp = add_or_update_env(*envp, key, equal + 1);
	free(key);
}

static void	handle_export_without_value(char *arg, char ***envp)
{
	int	index;

	index = find_env_index(*envp, arg);
	if (index == -1)
		*envp = add_env_without_value(*envp, arg);
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
			handle_export_with_value(cmd->args[i], envp);
		else
			handle_export_without_value(cmd->args[i], envp);
		i++;
	}
	g_last_status = 0;
}
