/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhijazi <jhijazi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:21:00 by jhijazi           #+#    #+#             */
/*   Updated: 2025/11/27 19:26:48 by jhijazi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
#include "token.h"

// Global variable for last exit status
extern int g_last_status;

// Structures
typedef struct s_redir
{
    char            *filename;
    t_token_type    type;
    struct s_redir  *next;
}   t_redir;

typedef struct s_cmd
{
    char            **args;
    t_redir         redir_in;
    t_redir         redir_out;
    int             pipe_fd[2];
    struct s_cmd    *next;
    struct s_cmd    *prev;
}   t_cmd;

// Execution functions
void    execute_single_command(t_cmd *cmd, char ***envp);
char    *find_path(char *cmd, char **envp);
char    *get_env_value(const char *name, char **envp);
void    free_split(char **split);

// Built-in detection and execution
int     is_builtin(char *cmd);
int     execute_builtin(t_cmd *cmd, char ***envp);

// Built-in commands
void    built_in_pwd(void);
void    built_in_echo(t_cmd *cmd);
void    built_in_cd(char *path);
void    built_in_env(char **envp);
void    built_in_exit(t_cmd *cmd);
void    built_in_export(t_cmd *cmd, char ***envp);
void    built_in_unset(t_cmd *cmd, char ***envp);

// Environment manipulation
char    **add_or_update_env(char **envp, char *key, char *value);
char    **remove_env(char **envp, char *key);
int     find_env_index(char **envp, char *key);
void    print_export(char **envp);

// Redirection handling
int     handle_redirections(t_redir *redirections);

//tokenization
t_token *tokenization(char *input);

#endif