/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 12:50:30 by aawad             #+#    #+#             */
/*   Updated: 2026/01/04 12:53:25 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_var_with_quotes(char *env_str)
{
	char	*equal;
	int		i;

	equal = ft_strchr(env_str, '=');
	if (!equal)
	{
		ft_printf("declare -x %s\n", env_str);
		return ;
	}
	i = 0;
	ft_printf("declare -x ");
	while (env_str[i] && env_str[i] != '=')
	{
		ft_putchar_fd(env_str[i], 1);
		i++;
	}
	ft_printf("=\"");
	i++;
	while (env_str[i])
	{
		ft_putchar_fd(env_str[i], 1);
		i++;
	}
	ft_printf("\"\n");
}

void	print_export(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		print_var_with_quotes(envp[i]);
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
		if (!ft_strncmp(envp[i], key, len))
		{
			if (envp[i][len] == '=' || envp[i][len] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}
