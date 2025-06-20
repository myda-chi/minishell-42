#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"


/* Token types */
typedef enum e_token_type
{
	WORD,           // Regular command or argument
	PIPE,           // |
	REDIR_IN,       // <  
	REDIR_OUT,      // > same as truncate
	REDIR_APPEND,   // >>
	REDIR_HEREDOC,  // << ok
	END             // End of input
} t_token_type;

typedef struct s_token
{
	struct s_token	*next;
	t_token_type    type;
	char    		*value;
} t_token;

typedef struct s_tokenizer
{
	struct s_token	*head;
	char    		*input;
	int     		pos;
	int     		len;
	int				error;
}	t_tokenizer;


/* Tokenizer functions */
t_tokenizer		*init_tokenizer(char *input);
t_tokenizer		*tokenize(t_tokenizer *tokens);
void			free_tokens(t_tokenizer *tokens);

/* Error handling */
int       		check_syntax(t_tokenizer *tokens);
void      		print_syntax_error(char *error);

/* Token creation and management */
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_tokenizer *tokens, t_token *new_token);
t_token_type	get_special_token_type(char c, char next);

/* String functions */
char			*extract_quoted_content(t_tokenizer *tokens, int start, int end);
int				handle_quotes(t_tokenizer *tokens);
int				is_special_char(char c);

t_token 		*handle_special_char(t_tokenizer *tokens);
t_token 		*handle_regular_word(t_tokenizer *tokens);
void			dig_prompt();

#endif 