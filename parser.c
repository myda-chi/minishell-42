#include "parser.h"

t_token *tokenize(t_parser *parser)
{
    int word_start;

    while (parser->pos < parser->len)
    {
        /* Skip whitespace */
        while (parser->pos < parser->len && ft_isspace(parser->input[parser->pos]))
            parser->pos++;
        
        if (parser->pos >= parser->len)
            break;

        /* Handle quotes */
        if (handle_quotes(parser, &word_start))
            continue;

        /* Handle environment variables */
        if (handle_env_var(parser))
            continue;

        /* Handle special characters */
        if (is_special_char(parser->input[parser->pos]))
        {
            add_token(&parser->tokens, handle_special_char(parser));
            continue;
        }

        /* Handle regular words */
        add_token(&parser->tokens, handle_regular_word(parser));
    }

    return (parser->tokens);
}
t_token *handle_special_char(t_parser *parser)
{
    t_token_type type;
    char *word;

    type = get_special_token_type(parser->input[parser->pos], 
                                parser->input[parser->pos + 1]);
    
    if (type == REDIR_HEREDOC || type == REDIR_APPEND)
    {
        word = ft_substr(parser->input, parser->pos, 2);
        parser->pos += 2;
    }
    else
    {
        word = ft_substr(parser->input, parser->pos, 1);
        parser->pos++;
    }
    return (create_token(type, word));
}
t_token *handle_regular_word(t_parser *parser)
{
    char *word;
    int word_start;

    word_start = parser->pos;
    while (parser->pos < parser->len && 
           !ft_isspace(parser->input[parser->pos]) && 
           !is_special_char(parser->input[parser->pos]))
        parser->pos++;
    
    word = ft_substr(parser->input, word_start, parser->pos - word_start);
    return (create_token(WORD, word));
} 