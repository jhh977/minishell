CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

NAME    = minishell
HEAD    = minishell.h
SRCS    = main.c tokenization.c token.c tokenization_quotes.c


OBJS    = $(SRCS:.c=.o)
LIBFT_DIR	= libft
LIBFT	= libft/libft.a
INCLUDES	= -Ilibft
LIBS	= -Llibft -lft

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft $(INCLUDES) -o $(NAME) -lreadline
		@echo "Library [$(NAME)] created!"

%.o: %.c $(HEAD)
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
		make -C $(LIBFT_DIR)

clean:
		@rm -f $(OBJS)
		@make -C $(LIBFT_DIR) clean
		@echo "Objects removed!"

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIBFT_DIR) fclean
		@echo "Library [$(NAME)] removed!"

re:		fclean all