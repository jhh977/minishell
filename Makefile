CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

NAME    = minishell
HEAD    = minishell.h

# Parsing & Tokenization (current directory)
PARSE_SRCS =parsing/tokenization.c \
            parsing/token.c\
            parsing/tokenization_quotes.c\
            parsing/tokenization_helper.c\
            parsing/local_var_helper.c\
            parsing/add_word.c \
            parsing/parse_checker.c\
            parsing/parser.c\
            parsing/cmd_helper.c\
            parsing/redirs_handler.c \
            parsing/free_functions_parsing.c\
            parsing/signals.c\
            parsing/signals_helper.c

# Execution & Built-ins (in execution/ directory)
EXEC_SRCS = execution/built_in_command1.c \
            execution/built_in_command2.c \
            execution/built_in_command3.c \
            execution/built_in_execution.c \
            execution/built_in_redirection.c \
            execution/find_path.c \
            execution/heredoc.c \
            execution/handel_redirection1.c \
            execution/handel_redirection2.c \
            execution/handel_single_execution.c \
            execution/pipline_command.c \
            execution/pipline_execute.c \
            execution/remove_add_env.c \
            execution/wait_execute_pipeline.c

# Main
MAIN_SRC = main.c

SRCS    = $(MAIN_SRC) $(PARSE_SRCS) $(EXEC_SRCS)
OBJS    = $(SRCS:.c=.o)

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a
INCLUDES    = -I. -Ilibft
LIBS        = -Llibft -lft

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -lreadline -o $(NAME)
	@echo "[$(NAME)] created successfully!"

%.o: %.c $(HEAD)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@echo "Object files removed!"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "[$(NAME)] removed!"

re: fclean all