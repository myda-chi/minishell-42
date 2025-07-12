#include "parser.h"
int	skip_whitespace(t_tokenizer *tokens)
{
	while (tokens->pos < tokens->len && ft_isspace(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos < tokens->len);
}

int	is_quote_char(char c)
{
	return (c == '\'' || c == '"');
}
int	is_word_char(char c)
{
	return (!ft_isspace(c) && !is_special_char(c) && !is_quote_char(c));
}

int	get_word_length(t_tokenizer *tokens)
{
	int	start;

	start = tokens->pos;
	while (tokens->pos < tokens->len && is_word_char(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos - start);
}
int	add_end_token(t_tokenizer *tokens)
{
	t_token	*end_token;

	end_token = create_token(END, NULL);
	if (!end_token)
		return (0);
	add_token(tokens, end_token);
	return (1);
}