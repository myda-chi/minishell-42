#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

/* Token Types */
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

/* Token Structure */
typedef struct s_token
{
	struct s_token	*next;
	t_token_type    type;
	char    		*value;
} t_token;

/* Tokenizer Structure */
typedef struct s_tokenizer
{
	struct s_token	*head;
	char    		*input;
	int     		pos;
	int     		len;
	int				error;
}	t_tokenizer;

/* Lexer Functions */
t_tokenizer		*init_tokenizer(char *input);
t_tokenizer		*tokenize(t_tokenizer *tokens);
void			free_tokens(t_tokenizer *tokens);

/* Token Functions */
t_token			*create_token(t_token_type type, char *value);
void			add_token(t_tokenizer *tokens, t_token *new_token);
t_token_type	get_special_token_type(char c, char next);

/* Parser Functions */
t_command		*build_simple_command(t_token **current, t_shell_state *state);
t_command		*build_commands(t_tokenizer *tokens, t_shell_state *state);
t_command		*parse_command(char *input, t_shell_state *state);

/* Command Building Helpers */
int				count_word_tokens(t_token *tokens);
t_command		*init_command(int argc);

/* Redirection Handling */
t_in_redir		*handle_in_redirection(t_token **current);
t_out_redir		*handle_out_redirection(t_token **current);
int				add_redirection_to_command(t_command *cmd, t_token **current);

/* Pipeline Functions */
int				validate_pipeline_syntax(t_token *tokens);

/* Memory Management */
void			free_command(t_command *cmd);
void			free_commands(t_command *commands);

/* Quote Handling */
char			*extract_quoted_content(t_tokenizer *tokens, int start, int end);
int				handle_quotes(t_tokenizer *tokens);

/* Token Utilities */
int				is_special_char(char c);
t_token 		*handle_special_char(t_tokenizer *tokens);
t_token 		*handle_regular_word(t_tokenizer *tokens);
t_in_redir *create_in_redirection(t_token **current);
int	handle_out_redirection_command(t_command *cmd, t_token **current);
int	handle_in_redirection_command(t_command *cmd, t_token **current);
/* Error Handling */
void      		print_syntax_error(char *error);
int populate_command_arguments(t_command *cmd, t_token **current, t_shell_state *state);
int process_word_token(t_command *cmd, int *i, t_token **current, t_shell_state *state);
t_command *build_command_list(t_token *tokens, t_shell_state *state);
/* Prompt */
void			dig_prompt(void);
int	is_word_char(char c);
int	skip_whitespace(t_tokenizer *tokens);
int	is_operator(char c);
int	handle_single_quote(t_tokenizer *tokens, int start);
int	handle_double_quote(t_tokenizer *tokens, int start);
int	add_end_token(t_tokenizer *tokens);
int	process_token(t_tokenizer *tokens);
char	*extract_special_token_value(t_tokenizer *tokens, int len);
int	get_word_length(t_tokenizer *tokens);
int	is_quote_char(char c);
int	is_wrd_char(char c);
#endif 