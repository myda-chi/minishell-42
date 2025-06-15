#ifndef PARSER_H
# define PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/* Token types */
typedef enum e_token_type
{
    WORD,           // Regular command or argument
    PIPE,           // |
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    REDIR_HEREDOC,  // <<
    SINGLE_QUOTE,   // '
    DOUBLE_QUOTE,   // "
    DOLLAR,         // $
    END             // End of input
} t_token_type;

#define R "\033[31m"
#define G  "\033[32m"
#define Y "\033[33m"
#define B   "\033[34m"

/* Token structure */
typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
} t_token;

/* Parser structure */
typedef struct s_parser
{
    char    *input;
    int     pos;
    int     len;
    t_token *tokens;
} t_parser;

/* Parser functions */
t_parser  *init_parser(char *input);
void      free_parser(t_parser *parser);
t_token   *tokenize(t_parser *parser);
void      free_tokens(t_token *tokens);

/* Error handling */
int       check_syntax(t_token *tokens);
void      print_syntax_error(char *error);

/* Token creation and management */
t_token   *create_token(t_token_type type, char *value);
void      add_token(t_token **tokens, t_token *new_token);

/* Quote and environment handling */
char      *extract_quoted_content(t_parser *parser, int start, int end);
int       handle_quotes(t_parser *parser, int *word_start);
int       handle_env_var(t_parser *parser);
char      *expand_env_var(t_parser *parser);
int is_special_char(char c);
t_token_type get_special_token_type(char c, char next);
t_token *handle_special_char(t_parser *parser);
t_token *handle_regular_word(t_parser *parser);
void    dig_prompt();

#endif 