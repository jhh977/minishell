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
	END_OF_INPUT,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_token_helper
{
	int	start;
	int	end;
	t_token	*head;
	t_token	*tail;
	char *word;
	int dquote;
	int squote;
} t_token_helper;
#endif