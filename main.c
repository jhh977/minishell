/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad <aawad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 13:57:06 by jhh               #+#    #+#             */
/*   Updated: 2026/01/04 00:09:43 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_status = 0;

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
	free_tokens(tokens);
	if (!cmd_list)
	{
		return ;
	}
	if (is_pipeline(cmd_list))
		execute_pipeline(cmd_list, envp);
	else
		execute_single_command(cmd_list, envp);
	free_cmd_list(cmd_list);
}

static void	run_shell(char ***my_envp)
{
	char	*input;

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
			process_input(input, my_envp);
		setup_interactive_signals();
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**my_envp;

	(void)argc;
	(void)argv;
	my_envp = copy_envp(envp);
	if (!my_envp)
	{
		ft_putstr_fd("minishell: failed to initialize environment\n", 2);
		return (1);
	}
	run_shell(&my_envp);
	free_envp(my_envp);
	rl_clear_history();
	return (g_last_status);
}
