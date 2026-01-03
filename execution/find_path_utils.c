/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 13:25:44 by aawad             #+#    #+#             */
/*   Updated: 2026/01/03 13:26:13 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_in_paths(char **paths, char *cmd)
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
		if (access(full, X_OK) == 0 && !is_directory(full))
			return (free_split(paths), full);
		free(full);
		j++;
	}
	return (NULL);
}
