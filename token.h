#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC,
	SPACE,
	END_OF_INPUT,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;