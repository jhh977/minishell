/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:05:30 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/04 19:13:27 by jhijazi          ###   ########.fr       */
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

int main(void)
{
    char        *a;
    t_token     *head;
    t_token     *tmp;

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
        tmp = head;

        check_parse(head);
        // while (tmp)
        // {
        //     printf("[%s],[%s]\n", tmp->value, get_token_type_name(tmp->type));
        //     tmp = tmp->next;
        // }
        
        free_tokens(head);
        free(a);
    }
    return (0);
}
