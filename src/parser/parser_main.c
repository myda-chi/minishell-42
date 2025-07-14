/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 19:20:14 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 19:21:59 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*parse_command(char *input, t_shell_state *state)
{
	t_tokenizer	*tokenizer;
	t_command	*commands;

	if (!input || !*input)
		return (NULL);
	tokenizer = init_tokenizer(input);
	if (!tokenizer)
		return (NULL);
	tokenizer = tokenize(tokenizer);
	if (!tokenizer)
		return (NULL);
	commands = build_commands(tokenizer, state);
	free_tokens(tokenizer);
	free(tokenizer);
	return (commands);
}
