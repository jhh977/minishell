/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:59:14 by aawad             #+#    #+#             */
/*   Updated: 2025/11/08 19:59:30 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*save_std_fds(void)
{
	int	*saved_fds;

	saved_fds = malloc(sizeof(int) * 2);
	if (!saved_fds)
		return (NULL);
	saved_fds[0] = dup(STDIN_FILENO);
	saved_fds[1] = dup(STDOUT_FILENO);
	if (saved_fds[0] < 0 || saved_fds[1] < 0)
	{
		if (saved_fds[0] >= 0)
			close(saved_fds[0]);
		if (saved_fds[1] >= 0)
			close(saved_fds[1]);
		free(saved_fds);
		return (NULL);
	}
	return (saved_fds);
}

void	restore_std_fds(int *saved_fds)
{
	if (!saved_fds)
		return ;
	if (saved_fds[0] >= 0)
	{
		dup2(saved_fds[0], STDIN_FILENO);
		close(saved_fds[0]);
	}
	if (saved_fds[1] >= 0)
	{
		dup2(saved_fds[1], STDOUT_FILENO);
		close(saved_fds[1]);
	}
	free(saved_fds);
}
