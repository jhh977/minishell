/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad & jhijazi                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 15:09:01 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/25 00:00:00 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Signal handler for interactive mode (main shell prompt)
** Handles Ctrl+C (SIGINT) by:
** 1. Printing a newline
** 2. Clearing the current line in readline
** 3. Moving to a new line
** 4. Redisplaying the prompt
** Sets exit status to 130 (128 + SIGINT)
*/
void	sigint_handler(int sig)
{
	(void)sig;
	g_last_status = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}


void	sigint_heredoc_handler(int sig)
{
	(void)sig;
	g_last_status = 130;
	close(STDIN_FILENO);
	write(1, "\n", 1);
}


void setup_interactive_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = sigint_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    signal(SIGQUIT, SIG_IGN); 
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}


void	setup_heredoc_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_heredoc_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}


void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}