#include "parser.h"

static t_in_redir *handle_in_redirection(t_token **current)
{
	t_in_redir *redir;

	redir = malloc(sizeof(t_in_redir));
	if (!redir)
		return (NULL);
	redir->in_mode = (*current)->type == REDIR_IN ? 0 : 1;
	*current = (*current)->next;
	if (*current && (*current)->type == WORD)
	{
		if (redir->in_mode == 1)
			redir->delimeter = ft_strdup((*current)->value);
		else
			redir->in_file = ft_strdup((*current)->value);
	}
	redir->next = NULL;
	return (redir);
}

static t_out_redir *handle_out_redirection(t_token **current)
{
	t_out_redir *redir;

	redir = malloc(sizeof(t_out_redir));
	if (!redir)
		return (NULL);
	redir->out_mode = (*current)->type == REDIR_OUT ? 0 : 1;
	*current = (*current)->next;
	if (*current && (*current)->type == WORD)
		redir->out_file = ft_strdup((*current)->value);
	redir->next = NULL;
	return (redir);
}

static int count_args(t_token *tokens)
{
	int count;

	count = 0;
	while (tokens && tokens->type != PIPE)
	{
		if (tokens->type == WORD)
			count++;
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_HEREDOC
			|| tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
			tokens = tokens->next;
		if (tokens)
			tokens = tokens->next;
	}
	return (count);
}

t_command *build_simple_command(t_token **current)
{
	t_command *cmd;
	t_in_redir *in_redir_tail;
	t_out_redir *out_redir_tail;
	int i;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argc = count_args(*current);
	cmd->argv = ft_calloc(cmd->argc + 1, sizeof(char *));
	if (!cmd->argv)
		return (free(cmd), NULL);
	in_redir_tail = NULL;
	out_redir_tail = NULL;
	i = 0;
	while (*current && (*current)->type != PIPE)
	{
		if ((*current)->type == WORD)
			cmd->argv[i++] = ft_strdup((*current)->value);
		else if ((*current)->type == REDIR_IN || (*current)->type == REDIR_HEREDOC)
		{
			if (!in_redir_tail)
			{
				cmd->in_redir = handle_in_redirection(current);
				in_redir_tail = cmd->in_redir;
			}
			else
			{
				in_redir_tail->next = handle_in_redirection(current);
				in_redir_tail = in_redir_tail->next;
			}
		}
		else if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_APPEND)
		{
			if (!out_redir_tail)
			{
				cmd->out_redir = handle_out_redirection(current);
				out_redir_tail = cmd->out_redir;
			}
			else
			{
				out_redir_tail->next = handle_out_redirection(current);
				out_redir_tail = out_redir_tail->next;
			}
		}
		*current = (*current)->next;
	}
	return (cmd);
}

t_command *build_commands(t_tokenizer *tokens)
{
	t_token		*current;
	t_command	*head;
	t_command	*cmd_tail;

	current = tokens->head;
	if (!current)
		return (NULL);
	head = build_simple_command(&current);
	cmd_tail = head;
	while (current)
	{
		if (current->type == PIPE)
		{
			current = current->next;
			if (!current)
				return (head); // syntax error, pipe at the end
			cmd_tail->next = build_simple_command(&current);
			if (!cmd_tail->next)
				return (head); // Should free head
			cmd_tail = cmd_tail->next;
		}
		else
		{
			// This case should not be reached if build_simple_command is correct
			current = current->next;
		}
	}
	return (head);
}

t_command *parse_command(char *input)
{
	t_tokenizer *tokenizer;
	t_command	*commands;

	if (!input || !*input)
		return (NULL);
	tokenizer = init_tokenizer(input);
	if (!tokenizer)
		return (NULL);
	tokenize(tokenizer);
	if (check_syntax(tokenizer))
	{
		free_tokens(tokenizer);
		return (NULL);
	}
	commands = build_commands(tokenizer);
	free_tokens(tokenizer);
	return (commands);
}