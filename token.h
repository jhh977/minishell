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

void	token_helper_init(t_token_helper *t);
t_token	*new_token(char *value);
int		quotes_check(t_token_helper t);
void	add_token_main(t_token_helper *t, char *input);
int		quotes_check(t_token_helper t);
void tokenize_quotes(t_token_helper *t, char *input);

#endif