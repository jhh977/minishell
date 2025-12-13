#include "minishell.h"
void	free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*join_path(char *dir, char *cmd)
{
	char	*full;
	int		len_dir;
	int		len_cmd;

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

static	char	*check_direct_path(char *cmd)
{
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

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*full;
	int		j;

	full = check_direct_path(cmd);
	if (full)
		return (full);
	paths = get_paths(envp);
	if (!paths)
		return (NULL);
	j = 0;
	while (paths[j])
	{
		full = join_path(paths[j], cmd);
		if (access(full, X_OK) == 0)
			return (free_split(paths), full);
		free(full);
		j++;
	}
	free_split(paths);
	return (NULL);
}
