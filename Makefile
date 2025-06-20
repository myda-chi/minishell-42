NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -L/mingw64/lib -lreadline
CPPFLAGS = -I/mingw64/include
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	main.c lexer.c lexer_init.c token.c token_utils.c error.c quote_handler.c \
		my_prompt.c parser.c executor.c utils.c signals.c \
		builtins/ft_echo.c builtins/ft_cd.c builtins/ft_pwd.c \
		builtins/ft_export.c builtins/ft_unset.c builtins/ft_env.c \
		builtins/ft_exit.c

OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJS) $(LDFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 