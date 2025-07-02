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

    start++;
    len = end - start;
    content = ft_substr(tokens->input, start, len);
    return (content);
}

static t_token	*create_quoted_token(t_tokenizer *tokens, int start, int end)
{
	char	*content;

	content = extract_quoted_content(tokens, start, end);
	if (!content)
		return (NULL);
	return (create_token(WORD, content));
}

int handle_quotes(t_tokenizer *tokens)
{
    int		end;
    t_token	*token;

    if (!tokens || tokens->pos >= tokens->len)
        return (-1);
    if (tokens->input[tokens->pos] == '\'')
        end = handle_single_quote(tokens, tokens->pos);
    else if (tokens->input[tokens->pos] == '"')
        end = handle_double_quote(tokens, tokens->pos);
    else
        return (0);
    if (end == -1)
        return (-1);
    token = create_quoted_token(tokens, tokens->pos, end);
    if (!token)
        return (-1);
    add_token(tokens, token);
    tokens->pos = end + 1;
    return (1);
}
