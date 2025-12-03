/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihad <jihad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:05:30 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/03 22:04:49 by jihad            ###   ########.fr       */
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

        printf("Tokens:\n");
        while (tmp)
        {
            printf("[%s],[%s]\n", tmp->value, get_token_type_name(tmp->type));
            tmp = tmp->next;
        }

        free_tokens(head);
        free(a);
    }
    return (0);
}


// int main(int argc, char **argv)
// {
//     t_token *head;
//     t_token *tmp;
//     int i;

//     if (argc < 2)
//     {
//         printf("Usage: %s <command1> <command2> ...\n", argv[0]);
//         printf("Example: %s \"echo hello\" \"ls -l\" \"cat file.txt\"\n", argv[0]);
//         return (1);
//     }

//     i = 1;
//     while (i < argc)
//     {
//         printf("\n=== Processing command %d: '%s' ===\n", i, argv[i]);
        
//         head = tokenization(argv[i]);
//         if (!head)
//         {
//             printf("Error: Tokenization failed for command: %s\n", argv[i]);
//             i++;
//             continue;
//         }

//         tmp = head;
//         printf("Tokens:\n");
//         while (tmp)
//         {
//             printf("[%s],[%s]\n", tmp->value, get_token_type_name(tmp->type));
//             tmp = tmp->next;
//         }

//         free_tokens(head);
//         i++;
//     }
//     return (0);
// }