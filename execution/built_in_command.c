/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:40 by aawad             #+#    #+#             */
/*   Updated: 2025/11/08 19:43:53 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	built_in_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
//echo helllo / echo -n hello /echo

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	built_in_cd(t_cmd *cmd)
{
	char	*path;

	path = cmd->args[1];
	if (path)
		path = cmd->args[1];
	else
		getenv("HOME");
	if (chdir(path) != 0)
		perror("minishell: cd");
}

void	built_in_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	built_in_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->args[1] == NULL)
		exit(0);
	if (cmd->args[2] != NULL)
		fprintf(stderr, "minishell: exit: too many arguments\n");
}
