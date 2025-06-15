#include "parser.h"

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"' || c == '$');
}

t_token_type get_special_token_type(char c, char next)
{
    if (c == '|')
        return (PIPE);
    if (c == '<')
    {
        if(next == '<')
            return(REDIR_HEREDOC);
        return(REDIR_IN);
    }
        // return (next == '<' ? REDIR_HEREDOC : REDIR_IN);
    if (c == '>')
    {
        if(next == '>')
            return(REDIR_APPEND);
        return(REDIR_OUT);
    }
        // return (next == '>' ? REDIR_APPEND : REDIR_OUT);
    if (c == '\'')
        return (SINGLE_QUOTE);
    if (c == '"')
        return (DOUBLE_QUOTE);
    if (c == '$')
        return (DOLLAR);
    return (WORD);
}
