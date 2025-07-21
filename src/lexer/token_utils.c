/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:50:36 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/21 16:57:30 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

t_token_type	get_special_token_type(char c, char next)
{
	if (c == '|')
		return (PIPE);
	if (c == '<')
	{
		if (next == '<')
			return (REDIR_HEREDOC);
		return (REDIR_IN);
	}
	if (c == '>')
	{
		if (next == '>')
			return (REDIR_APPEND);
		return (REDIR_OUT);
	}
	return (WORD);
}

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

int	is_wrd_char(char c)
{
	return (!ft_isspace(c) && !is_special_char(c) && !is_quote_char(c));
}
