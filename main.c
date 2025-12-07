/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:05:30 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/07 20:31:43 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*get_token_type_name(t_token_type type)
{
	const char	*names[] = {
		"WORD",
		"PIPE", 
		"REDIR_IN",
		"REDIR_OUT",
		"REDIR_APPEND", 
		"REDIR_HEREDOC",
		"END_OF_INPUT"
	};
	
	if (type >= 0 && type <= END_OF_INPUT)
		return (names[type]);
	return ("UNKNOWN");
}

void	print_commands(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		i;

	current = cmd_list;
	while (current)
	{
		printf("Command:\n");
		
		// Print args
		printf("  Args: ");
		i = 0;
		while (i < current->arg_count)
		{
			printf("[%s] ", current->args[i]);
			i++;
		}
		printf("\n");
		
		// Print redirections
		if (current->redir_in.filename)
			printf("  Input redir: %s (type: %s)\n", 
				current->redir_in.filename, get_token_type_name(current->redir_in.type));
		if (current->redir_out.filename)
			printf("  Output redir: %s (type: %s)\n", 
				current->redir_out.filename, get_token_type_name(current->redir_out.type));
		
		printf("---\n");
		current = current->next;
	}
}

int main(void)
{
	char        *a;
	t_token     *head;
	// t_token     *tmp;
	t_cmd		*cmd;

	while (1)
	{
		a = readline("> ");
		if (!a)              // Ctrl-D
			break;

		if (ft_strncmp(a, "exit", 5) == 0)
		{
			free(a);
			break;
		}

		head = tokenization(a);
		// tmp = head;

		cmd = check_parse(head);
		print_commands(cmd);//here this one
		free_tokens(head);
		free(a);
	}
	return (0);
}
