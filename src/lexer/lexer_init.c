/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:28:01 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 20:15:29 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_tokenizer	*init_tokenizer(char *input)
{
	t_tokenizer	*tokenizer;

	tokenizer = (t_tokenizer *)malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	tokenizer->input = input;
	tokenizer->pos = 0;
	tokenizer->len = ft_strlen(input);
	tokenizer->head = NULL;
	tokenizer->error = 0;
	return (tokenizer);
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<' || c == ';' || c == '&' || c == '('
		|| c == ')');
}

int	handle_single_quote(t_tokenizer *tokens, int start)
{
	int	end;

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

int	handle_double_quote(t_tokenizer *tokens, int start)
{
	int	end;

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
