#include "parser.h"

static int	add_end_token(t_tokenizer *tokens)
{
	t_token	*end_token;

	end_token = create_token(END, NULL);
	if (!end_token)
		return (0);
	add_token(tokens, end_token);
	return (1);
}

static int	skip_whitespace(t_tokenizer *tokens)
{
	while (tokens->pos < tokens->len && ft_isspace(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos < tokens->len);
}

static int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}

static int	process_token(t_tokenizer *tokens)
{
	t_token	*new_token;
	int		quote_result;

	if (is_quote_char(tokens->input[tokens->pos]))
	{
		quote_result = handle_quotes(tokens);
		if (quote_result == -1)
			return (-1);
		return (quote_result);
	}
	if (is_special_char(tokens->input[tokens->pos]))
		new_token = handle_special_char(tokens);
	else
		new_token = handle_regular_word(tokens);
	if (!new_token)
		return (-1);
	add_token(tokens, new_token);
	return (1);
}

t_tokenizer *tokenize(t_tokenizer *tokens)
{
	int	result;

	if (!tokens)
		return (NULL);
	while (skip_whitespace(tokens))
	{
		result = process_token(tokens);
		if (result == -1)
		{
			free_tokens(tokens);
			return (NULL);
		}
	}
	if (!add_end_token(tokens))
	{
		free_tokens(tokens);
		return (NULL);
	}
	return (tokens);
}

static char	*extract_special_token_value(t_tokenizer *tokens, int len)
{
	char	*value;

	value = ft_substr(tokens->input, tokens->pos, len);
	if (!value)
		return (NULL);
	tokens->pos += len;
	return (value);
}

t_token *handle_special_char(t_tokenizer *tokens)
{
	t_token_type	type;
	char			*value;
	int				len;

	if (!tokens || tokens->pos >= tokens->len)
		return (NULL);
	type = get_special_token_type(tokens->input[tokens->pos], 
		tokens->pos + 1 < tokens->len ? tokens->input[tokens->pos + 1] : '\0');
	len = (type == REDIR_HEREDOC || type == REDIR_APPEND) ? 2 : 1;
	value = extract_special_token_value(tokens, len);
	if (!value)
		return (NULL);
	return (create_token(type, value));
}
static int	is_word_char(char c)
{
	return (!ft_isspace(c) && !is_special_char(c) && !is_quote_char(c));
}

static int	get_word_length(t_tokenizer *tokens)
{
	int	start;

	start = tokens->pos;
	while (tokens->pos < tokens->len && is_word_char(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos - start);
}

t_token *handle_regular_word(t_tokenizer *tokens)
{
	char	*value;
	int		word_start;
	int		word_len;

	if (!tokens || tokens->pos >= tokens->len)
		return (NULL);
	word_start = tokens->pos;
	word_len = get_word_length(tokens);
	if (word_len == 0)
		return (NULL);
	value = ft_substr(tokens->input, word_start, word_len);
	if (!value)
		return (NULL);
	return (create_token(WORD, value));
} 