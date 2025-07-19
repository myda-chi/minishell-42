/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:45:54 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/19 23:06:05 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	add_end_token(t_tokenizer *tokens)
{
	t_token	*end_token;

	end_token = create_token(END, NULL);
	if (!end_token)
		return (0);
	add_token(tokens, end_token);
	return (1);
}

int	process_token(t_tokenizer *tokens)
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

char	*extract_special_token_value(t_tokenizer *tokens, int len)
{
	char	*value;

	value = ft_substr(tokens->input, tokens->pos, len);
	if (!value)
		return (NULL);
	tokens->pos += len;
	return (value);
}

int	get_word_length(t_tokenizer *tokens)
{
	int	start;

	start = tokens->pos;
	while (tokens->pos < tokens->len
		&& is_wrd_char(tokens->input[tokens->pos]))
		tokens->pos++;
	return (tokens->pos - start);
}
