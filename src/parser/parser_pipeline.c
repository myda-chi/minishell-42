#include "parser.h"

int	validate_pipeline_syntax(t_token *tokens)
{
	t_token *current;

	current = tokens;
	if (!current || current->type == PIPE)
	{
		print_syntax_error("syntax error near unexpected token '|'");
		return (0);
	}
	while (current && current->type != END)
	{
		if (current->type == PIPE)
		{
			current = current->next;
			if (!current || current->type == PIPE || current->type == END)
			{
				print_syntax_error("syntax error near unexpected token '|'");
				return (0);
			}
		}
		else
			current = current->next;
	}
	return (1);
}

t_command *build_commands(t_tokenizer *tokens, t_shell_state *state)
{
	t_token		*current;
	t_command	*head;
	t_command	*tail;
	t_command	*new_cmd;

	if (!tokens || !tokens->head)
		return (NULL);
	if (!validate_pipeline_syntax(tokens->head))
		return (NULL);
	current = tokens->head;
	head = build_simple_command(&current, state);
	if (!head)
		return (NULL);
	tail = head;
	while (current && current->type == PIPE)
	{
		current = current->next;
		new_cmd = build_simple_command(&current, state);
		if (!new_cmd)
		{
			free_commands(head);
			return (NULL);
		}
		tail->next = new_cmd;
		tail = new_cmd;
	}
	return (head);
}
