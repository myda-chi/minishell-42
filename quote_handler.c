#include "parser.h"

static int handle_single_quote(t_parser *parser, int start)
{
    int end;

    end = start + 1;
    while (parser->input[end] && parser->input[end] != '\'')
        end++;
    if (!parser->input[end])
    {
        print_syntax_error("unclosed single quote");
        return (-1);
    }
    return (end);
}

static int handle_double_quote(t_parser *parser, int start)
{
    int end;

    end = start + 1;
    while (parser->input[end] && parser->input[end] != '"')
    {
        if (parser->input[end] == '\\' && parser->input[end + 1])
            end += 2;
        else
            end++;
    }
    if (!parser->input[end])
    {
        print_syntax_error("unclosed double quote");
        return (-1);
    }
    return (end);
}

char *extract_quoted_content(t_parser *parser, int start, int end)
{
    char *content;
    int len;

    len = end - start - 1;
    content = ft_substr(parser->input, start + 1, len);
    return (content);
}

int handle_quotes(t_parser *parser, int *word_start)
{
    (void)word_start;
    int end;
    char *content;

    if (parser->input[parser->pos] == '\'')
    {
        end = handle_single_quote(parser, parser->pos);
        if (end == -1)
            return (0);
        content = extract_quoted_content(parser, parser->pos, end);
        add_token(&parser->tokens, create_token(SINGLE_QUOTE, content));
        parser->pos = end + 1;
        return (1);
    }
    else if (parser->input[parser->pos] == '"')
    {
        end = handle_double_quote(parser, parser->pos);
        if (end == -1)
            return (0);
        content = extract_quoted_content(parser, parser->pos, end);
        add_token(&parser->tokens, create_token(DOUBLE_QUOTE, content));
        parser->pos = end + 1;
        return (1);
    }
    return (0);
}