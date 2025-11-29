/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_add_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 14:13:19 by aawad             #+#    #+#             */
/*   Updated: 2025/11/24 14:13:34 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_env_var(char *key, char *value)
{
	char	*tmp;
	char	*new_var;

	tmp = ft_strjoin(key, "=");
	new_var = ft_strjoin(tmp, value);
	free(tmp);
	return (new_var);
}

char	**add_or_update_env(char **envp, char *key, char *value)
{
	int		index;
	int		count;
	char	**new_env;

	index = find_env_index(envp, key);
	if (index >= 0)
	{
		free(envp[index]);
		envp[index] = build_env_var(key, value);
		return (envp);
	}
	count = 0;
	while (envp[count])
		count++;
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (envp);
	count = -1;
	while (envp[++count])
		new_env[count] = envp[count];
	new_env[count] = build_env_var(key, value);
	return (new_env);
	new_env[count + 1] = NULL;
	free(envp);
}

char	**remove_env(char **envp, char *key)
{
	int		index;
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
		return (envp);
	count = 0;
	while (*envp)
	{
		if (count != index)
			*new_env++ = *envp;
		else
			free(*envp);
		envp++;
		count++;
	}
	*new_env = NULL;
	return (new_env - count);
}
