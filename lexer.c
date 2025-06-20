#include "parser.h"

t_tokenizer *tokenize(t_tokenizer *tokens)
{
	int	handle_quote;

	while (tokens->pos < tokens->len)
	{
		/* Skip whitespace */
		while (tokens->pos < tokens->len && ft_isspace(tokens->input[tokens->pos]))
			tokens->pos++;
		if (tokens->pos >= tokens->len)
			break;
		if (tokens->input[tokens->pos] == '\'' || tokens->input[tokens->pos] == '"')
		{
			handle_quote = handle_quotes(tokens);
			if (handle_quote == -1) 
			{
				free_tokens(tokens);
				tokens = NULL;
				return (NULL);
			}
			if (handle_quote > 0)
				continue ;
		}

		/* Handle special characters */
		if (is_special_char(tokens->input[tokens->pos]))
		{
			add_token(tokens, handle_special_char(tokens));
			continue;
		}
		/* Handle regular words */
		add_token(tokens, handle_regular_word(tokens));
	}
	add_token(tokens, create_token(END, NULL));
	check_syntax(tokens);
	return (tokens);
}
t_token *handle_special_char(t_tokenizer *tokens)
{
	t_token_type type;
	char *word;

	type = get_special_token_type(tokens->input[tokens->pos], 
								tokens->input[tokens->pos + 1]);
	
	if (type == REDIR_HEREDOC || type == REDIR_APPEND)
	{
		word = ft_substr(tokens->input, tokens->pos, 2);
		tokens->pos += 2;
	}
	else
	{
		word = ft_substr(tokens->input, tokens->pos, 1);
		tokens->pos++;
	}
	return (create_token(type, word));
}
t_token *handle_regular_word(t_tokenizer *tokens)
{
	char *word;
	int word_start;

	word_start = tokens->pos;
	while (tokens->pos < tokens->len && 
		   !ft_isspace(tokens->input[tokens->pos]) && 
		   !is_special_char(tokens->input[tokens->pos]))
		tokens->pos++;
	
	word = ft_substr(tokens->input, word_start, tokens->pos - word_start);
	return (create_token(WORD, word));
} 