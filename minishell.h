/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:21:00 by jhijazi           #+#    #+#             */
/*   Updated: 2025/10/09 18:55:53 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_cmd {
    char    **args;
	char    *infile;
	char    *outfile;
	int     append;
	int     pipe_fd[2];
} t_cmd;

typedef struct s_parser {
    t_cmd   *cmds;
    int     cmd_count;
} t_parser;

#endif