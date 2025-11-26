/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:55:47 by aawad             #+#    #+#             */
/*   Updated: 2025/11/11 18:51:49 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

int	find_env_index(char **envp, char *key)
{
	int i;
	int len;

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
		return ;
	}
	while (cmd->args[i])
	{
		equal = ft_strchr(cmd->args[i], '=');
		if (equal)
		{
			*equal = '\0';
			*envp = add_or_update_env(*envp, cmd->args[i], equal + 1);
		}
		else
			*envp = add_or_update_env(*envp, cmd->args[i], "");
		i++;
	}
}
#pragma region  more then 25 lines
char	**add_or_update_env(char **envp, char *key, char *value)
{
	int		index;
	int		i;
	int		count;
	char	*tmp;
	char	*new_var;
	char	**new_env;

	index = find_env_index(envp, key);
	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (index >= 0)
	{
		free(envp[index]);
		envp[index] = new_var;
		return (envp);
	}
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free_split(envp);
	return (new_env);
}

char	**remove_env(char **envp, char *key)
{
	int		index;
	int		i;
	int		j;
	int		count;
	char	**new_env;

	index = find_env_index(envp, key);
	if (index == -1)
		return (envp);
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * count);
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (i != index)
		{
			new_env[j] = ft_strdup(envp[i]);
			j++;
		}
		i++;
	}
	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}char	**add_or_update_env(char **envp, char *key, char *value)
{
	int		index;
	int		i;
	int		count;
	char	*tmp;
	char	*new_var;
	char	**new_env;

	index = find_env_index(envp, key);
	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	if (index >= 0)
	{
		free(envp[index]);
		envp[index] = new_var;
		return (envp);
	}
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	free_split(envp);
	return (new_env);
}
	free(envp);
	return (new_env);
}
#pragma endregion

void	built_in_unset(t_cmd *cmd, char ***envp)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		*envp = remove_env(*envp, cmd->args[i]);
		i++;
	}
}
