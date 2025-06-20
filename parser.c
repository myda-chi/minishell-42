#include "parser.h"

t_command *build_pipe_cmd()
{
	t_command *cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->type = PIPES;
	cmd->argc = 1;
	cmd->argv = NULL;
	return (cmd);
}

int count_word_tokens(t_token *token)
{
	int len;
	t_token *current;

	current = token;
	len = 0;
	if (!current)
		return (0);
	while (current && current->type == WORD)
	{
		len++;
		current = current->next;
	}
	return len;
}

t_command *build_simple_command(t_token *current)
{
	t_command *cmd;
	int i;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	if (current->type == WORD)
	{
		cmd->argc = count_word_tokens(current);
		cmd->argv = malloc(sizeof(char *) * cmd->argc + 1);
		if (!cmd->argv)
		{
			free(cmd);
			return (NULL);
		}
		cmd->argv[cmd->argc] = NULL;
		i = 0;
		while (current && i < cmd->argc)
		{
			cmd->argv[i++] = current->value;
			current = current->next;
		}
	}
	else if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
	{
		// to handle in redirections;
	}
	else if (current->type == REDIR_OUT || current->type == REDIR_APPEND)
	{
		// to handle out redirections;
	}
	return cmd;
}

t_command *build_commands(t_tokenizer *tokens)
{
	t_token		*current;
	t_command	*head;
	t_command	*cmd;

	current = tokens->head;
	if (!current)
		return (NULL);
	head = build_simple_command(current);
	current = current->next;
	while (current && current->type != PIPE)
	{
		if (current->type == END)
			return (head);
		current = current->next;
	}
	cmd = head;
	while (current)
	{
		if (current->type == PIPE)
		{
			cmd->next = build_pipe_cmd();
			cmd = cmd->next;
		}
		else if (current->type == END)
			return (head);
		else
		{
			cmd->next = build_simple_command(current);
			cmd = cmd->next;
			while (current && current->type != PIPE)
			{
				if (current->type == END)
					return (head);
				current = current->next;
			}
		}
		current = current->next;
	}
	return (head);
}

t_command *parse_command(char *input)
{
	t_tokenizer *tokenizer;
	t_tokenizer *tokens;
	t_command *commands;

	tokenizer = init_tokenizer(input);
	if (!tokenizer)
		return (NULL);
	tokens = tokenize(tokenizer);
	if (!tokens)
	{
		free(tokenizer);
		return (NULL);
	}
	commands = build_commands(tokens);
	free(tokenizer);
	free_tokens(tokens);
	return (commands);
}