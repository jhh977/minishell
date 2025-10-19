/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:05:30 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/18 18:12:19 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(void)
{
    char *a;
    t_token *head;
    t_token *tmp;

    while (1)
    {
        a = readline("input$ ");
        if (!a)
            break;
        if (ft_strncmp(a, "exit", 4) == 0)
        {
            free(a);
            break;
        }

        head = tokenization(a);
        tmp = head;

        printf("Tokens:\n");
        while (tmp)
        {
            printf("[%s]\n", tmp->value);
            tmp = tmp->next;
        }

        // cleanup
        // free_tokens(head);
        free(a);
    }
    return (0);
}
