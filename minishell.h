/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhh <jhh@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:21:00 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/11 14:14:09 by jhh              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include "token.h"

typedef struct s_redir
{
	char			*filename;
	t_token_type	type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	int				arg_count;
	int				arg_cap;
    t_redir         redir_in;
    t_redir         redir_out;
    t_redir         *redirs;
	int				pipe_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

# include "parse.h"

t_token *tokenization(char *input);

#endif