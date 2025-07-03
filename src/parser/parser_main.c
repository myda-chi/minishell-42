#include "parser.h"

t_command *parse_command(char *input, t_shell_state *state)
{
	t_tokenizer *tokenizer;
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
