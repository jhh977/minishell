/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 16:57:40 by aawad             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/11/24 13:16:27 by aawad            ###   ########.fr       */
=======
/*   Updated: 2025/11/08 19:43:53 by aawad            ###   ########.fr       */
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
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
<<<<<<< HEAD
		g_last_status = 1;
=======
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}
<<<<<<< HEAD
=======
//echo helllo / echo -n hello /echo
>>>>>>> eee43455382b4f5868def40d6323bf9575792024

void	built_in_echo(t_cmd *cmd)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
<<<<<<< HEAD
	if (cmd->args[i] && ft_strcmp(cmd->args[i], "-n") == 0)
=======
	if (cmd->args[i] && ft_strncmp(cmd->args[i], "-n", 3) == 0)
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
	{
		newline = 0;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
<<<<<<< HEAD
		i++;
	}
	if (newline)
		printf("\n");
	g_last_status = 0;
}

void	built_in_cd(t_cmd *cmd, char ***envp)
{
	char	*path;
	char	*home;

	if (cmd->args[1])
		path = cmd->args[1];
	else
	{
		home = get_env_value("HOME", *envp);
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			g_last_status = 1;
			return ;
		}
		path = home;
	}
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		g_last_status = 1;
	}
	else
		g_last_status = 0;
	if (!cmd->args[1])
		free(path);
}

void	built_in_env(char ***envp)
=======
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
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
{
	int	i;

	i = 0;
<<<<<<< HEAD
	while ((*envp)[i])
	{
		printf("%s\n", (*envp)[i]);
		i++;
	}
	g_last_status = 0;
=======
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
>>>>>>> eee43455382b4f5868def40d6323bf9575792024
}
