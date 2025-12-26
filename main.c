/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 13:57:06 by jhh               #+#    #+#             */
/*   Updated: 2025/12/26 14:22:08 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_status = 0;

static char	**copy_envp(char **envp)
{
	int		i;
	int		count;
	char	**new_envp;

	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[count] = NULL;
	return (new_envp);
}

static void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static void	process_input(char *input, char ***envp)
{
	t_token	*tokens;
	t_cmd	*cmd_list;

	add_history(input);
	if (!input || !*input)
		return ;
	tokens = tokenization(input, envp);
	if (!tokens)
		return ;
	cmd_list = check_parse(tokens);
	if (!cmd_list)
	{
		free_tokens(tokens);
		return ;
	}
	if (is_pipeline(cmd_list))
		execute_pipeline(cmd_list, envp);
	else
		execute_single_command(cmd_list, envp);
	free_cmd_list(cmd_list);
	free_tokens(tokens);
}

static int	envp_check(char **my_envp)
{
	if (!my_envp)
	{
		ft_putstr_fd("minishell: failed to initialize environment\n", 2);
		g_last_status = 1;
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**my_envp;

	(void)argc;
	(void)argv;
	my_envp = copy_envp(envp);
	if (!envp_check(envp))
		return (0);
	setup_interactive_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*input)
			process_input(input, &my_envp);
		setup_interactive_signals();
		free(input);
	}
	free_envp(my_envp);
	return (g_last_status);
}
