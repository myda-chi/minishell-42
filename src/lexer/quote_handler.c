#include "parser.h"

static int handle_single_quote(t_tokenizer *tokens, int start)
{
    int end;

    end = start + 1;
    while (end < tokens->len && tokens->input[end] != '\'')
        end++;
    if (end >= tokens->len || tokens->input[end] != '\'')
    {
        print_syntax_error("unclosed single quote");
        return (-1);
    }
    return (end);
}

static int handle_double_quote(t_tokenizer *tokens, int start)
{
    int end;

    end = start + 1;
    while (end < tokens->len && tokens->input[end] != '"')
    {
        if (tokens->input[end] == '\\' && end + 1 < tokens->len)
            end += 2;
        else
            end++;
    }
    if (end >= tokens->len || tokens->input[end] != '"')
    {
        print_syntax_error("unclosed double quote");
        return (-1);
    }
    return (end);
}

char *extract_quoted_content(t_tokenizer *tokens, int start, int end)
{
    char *content;
    int len;

    // start++;
    len = end - start;
    content = ft_substr(tokens->input, start, len);
    return (content);
}

static t_token	*create_quoted_token(t_tokenizer *tokens, int start, int end)
{
	char	*content;

	content = extract_quoted_content(tokens, start, end +1);
	if (!content)
		return (NULL);
	return (create_token(WORD, content));
}

static int is_operator(char c)
{
    return (c == '|' || c == '>' || c == '<' ||
            c == ';' || c == '&' || c == '(' ||
            c == ')');
}

int handle_quotes(t_tokenizer *tokens)
{
    int     start;
    int     end;
    t_token *token;

    if (!tokens || tokens->pos >= tokens->len)
        return (-1);
    
    start = tokens->pos;
    end = start;
    
    while (end < tokens->len && !ft_isspace(tokens->input[end]) && 
           !is_operator(tokens->input[end]))
    {
        if (tokens->input[end] == '\'')
        {
            int quote_end = handle_single_quote(tokens, end);
            if (quote_end == -1)
                return (-1);
            end = quote_end;
        }
        else if (tokens->input[end] == '"')
        {
            int quote_end = handle_double_quote(tokens, end);
            if (quote_end == -1)
                return (-1);
            end = quote_end;
        }
        end++;
    }

    token = create_quoted_token(tokens, start, end);
    if (!token)
        return (-1);
    add_token(tokens, token);
    tokens->pos = end;
    return (1);
}
