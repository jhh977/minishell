/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:53:41 by jhh               #+#    #+#             */
/*   Updated: 2025/12/30 10:15:43 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_path(char *dir, char *cmd)
{
	char	*full;
	int		len_dir;
	int		len_cmd;

	if (!cmd || !dir)
		return (NULL);
	len_cmd = ft_strlen(cmd);
	len_dir = ft_strlen(dir);
	full = malloc(len_dir + len_cmd + 2);
	if (!full)
		return (NULL);
	ft_strcpy(full, dir);
	full[len_dir] = '/';
	ft_strcpy(full + len_dir + 1, cmd);
	return (full);
}

static char	*check_direct_path(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

static char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
}

static char	*search_in_paths(char **paths, char *cmd)
{
	char	*full;
	int		j;

	j = 0;
	while (paths[j])
	{
		full = join_path(paths[j], cmd);
		if (!full)
		{
			free_split(paths);
			return (NULL);
		}
		if (access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
		j++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full;

	full = check_direct_path(cmd);
	if (full)
		return (full);
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	full = search_in_paths(paths, cmd);
	if (!full)
		free_split(paths);
	return (full);
}
