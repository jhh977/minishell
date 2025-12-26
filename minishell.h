/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aawad & jhijazi                             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 16:21:00 by jhijazi           #+#    #+#             */
/*   Updated: 2025/12/10 00:00:00 by aawad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _POSIX_C_SOURCE 200809L
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
extern int	g_last_status;

#define HEREDOC_INTERRUPTED -2

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	END_OF_INPUT,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_token_helper
{
	int				start;
	int				end;
	t_token			*head;
	t_token			*tail;
	char			*word;
	int				dquote;
	int				squote;
	t_token_type	type;
	int				execcode;
	char			**envp;
}	t_token_helper;

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
	t_redir			redir_in;
	t_redir			redir_out;
	t_redir         *redirs;
	int				pipe_fd[2];
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

// ExecutioN
void	execute_single_command(t_cmd *cmd, char ***envp);
void	execute_pipeline(t_cmd *cmd_list, char ***envp);
int		is_pipeline(t_cmd *cmd_list);
char	*find_path(char *cmd, char **envp);
char	*get_env_value(const char *name, char **envp);
void	free_split(char **split);
void	exec_child_process(t_cmd *cmd, char ***envp);

// Pipeline
int		count_commands(t_cmd *cmd_list);
int		**create_pipes(int num_cmds);
void	close_all_pipes(int **pipes, int num_pipes);
void	free_pipes(int **pipes, int num_pipes);
void	setup_pipe_fds(int cmd_index, int num_cmds, int **pipes);
int		wait_for_children(pid_t *pids, int num_cmds);

// Built-ins
int		built_in(char *cmd);
void	execute_builtin(t_cmd *cmd, char ***envp);
void	built_in_pwd(void);
void	built_in_echo(t_cmd *cmd);
void	built_in_cd(t_cmd *cmd, char **envp);
void	built_in_env(char **envp);
void	built_in_exit(t_cmd *cmd);
void	built_in_export(t_cmd *cmd, char ***envp);
void	built_in_unset(t_cmd *cmd, char ***envp);

// Environment
char	**add_or_update_env(char **envp, char *key, char *value);
char	**remove_env(char **envp, char *key);
int		find_env_index(char **envp, char *key);
void	print_export(char **envp);

// Redirections
int		handle_redirections(t_cmd *cmd);
int		handle_redir_in(char *file);
int		handle_redir_out(char *file);
int		handle_redir_append(char *file);
int		handle_redir_heredoc(char *delimiter);
int		open_fd(char *file, int flags, int mode);
int		dup_and_close(int fd, int target);
int		handle_heredoc(char *delimiter);
// FD management
int		*save_std_fds(void);
void	restore_std_fds(int *saved_fds);

// Tokenization
t_token	*tokenization(char *input, char ***envp);
void	token_helper_init(t_token_helper *t, char **envp);
t_token	*new_token(t_token_helper *t);
int		quotes_check(t_token_helper t);
void	append_add_token(t_token_helper *t, char *input);
void	tokenize_quotes(t_token_helper *t, char *input);
void	append_word(t_token_helper *t, char *input);
void	append_reset(t_token_helper *t, char *input);
int		end_of_word(char c);
void	check_add_special(t_token_helper *t, char *input);
void	var_handler(t_token_helper *t, char *input);
void	add_token(t_token_helper *t, t_token *new);
void	handle_question_mark(t_token_helper *t, char *input);
void	free_tokens(t_token *head);

// Parsing
int		checker(t_token *tok);
t_cmd	*check_parse(t_token *head);
int		is_redir(t_token *tok);
int		handle_redir(t_token **token, t_cmd *cmd);
t_cmd	*create_cmd(void);
void	add_cmd_to_list(t_cmd **list, t_cmd *new_cmd);
void	free_cmd_list(t_cmd *cmd_list);
void	add_arg(t_cmd *cmd, char *value);

//Signals
void	setup_interactive_signals(void);
void	setup_child_signals(void);
void	setup_heredoc_signals(void);
void	ignore_signals(void);
void	sigint_handler(int sig);
void	sigint_heredoc_handler(int sig);

#endif