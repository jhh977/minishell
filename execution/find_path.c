/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 15:53:41 by jhh               #+#    #+#             */
/*   Updated: 2026/01/03 13:26:10 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

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

char	*check_direct_path(char *cmd)
{
	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) != 0)
			return (NULL);
		if (is_directory(cmd))
			return (NULL);
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	return (ft_split(envp[i] + 5, ':'));
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
