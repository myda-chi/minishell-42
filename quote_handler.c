#include "parser.h"

static int handle_single_quote(t_tokenizer *tokens, int start)
{
    int end;

    end = start + 1;
    while (end < tokens->len && tokens->input[end] != '\'')
        end++;
    if (tokens->input[end] != '\'')
    {
        print_syntax_error("unclosed single quote");
        return (-1);
    }
    printf("%c\n", tokens->input[tokens->len]);
    if (tokens->input[end] && tokens->input[end] == '\'')
        end++;
    return (end);
}

static int handle_double_quote(t_tokenizer *tokens, int start)
{
    int end;

    end = start + 1;
    while (end < tokens->len && tokens->input[end] != '"')
    {
        if (tokens->input[end] == '\\' && tokens->input[end + 1])
            end += 2;
        else
            end++;
    }
    if (tokens->input[end] != '"')
    {
        print_syntax_error("unclosed double quote");
        return (-1);
    }
    if (tokens->input[end] && tokens->input[end] == '"')
        end++;
    return (end);
}

char *extract_quoted_content(t_tokenizer *tokens, int start, int end)
{
    char *content;
    int len;

    len = end - start;
    content = ft_substr(tokens->input, start, len);
    return (content);
}

int handle_quotes(t_tokenizer *tokens)
{
    int end;
    char *content;

    if (tokens->input[tokens->pos] == '\'')
    {
        end = handle_single_quote(tokens, tokens->pos);
        if (end == -1)
            return (-1);
        content = extract_quoted_content(tokens, tokens->pos, end);
        add_token(tokens, create_token(WORD, content));
        tokens->pos = end + 1;
        return (1);
    }
    else if (tokens->input[tokens->pos] == '"')
    {
        end = handle_double_quote(tokens, tokens->pos);
        if (end == -1)
            return (-1);
        content = extract_quoted_content(tokens, tokens->pos, end);
        add_token(tokens, create_token(WORD, content));
        tokens->pos = end + 1;
        return (1);
    }
    return (0);
}
