#include "parser.h"

static t_in_redir	*init_in_redir(int mode)
{
	t_in_redir *redir;

	redir = malloc(sizeof(t_in_redir));
	if (!redir)
		return (NULL);
	redir->in_mode = mode;
	redir->delimeter = NULL;
	redir->in_file = NULL;
	redir->next = NULL;
	return (redir);
}

t_in_redir	*handle_in_redirection(t_token **current)
{
	t_in_redir	*redir;
	int			mode;

	mode = (*current)->type == REDIR_IN ? 0 : 1;
	*current = (*current)->next;
	if (!*current || (*current)->type != WORD)
	{
		print_syntax_error("syntax error near unexpected token 'newline'");
		return (NULL);
	}
	redir = init_in_redir(mode);
	if (!redir)
		return (NULL);
	if (mode == 1)
		redir->delimeter = ft_strdup((*current)->value);
	else
		redir->in_file = ft_strdup((*current)->value);
	if ((mode == 1 && !redir->delimeter) || (mode == 0 && !redir->in_file))
		return (free(redir), NULL);
	return (redir);
}

t_out_redir *handle_out_redirection(t_token **current)
{
	t_out_redir *redir;

	redir = malloc(sizeof(t_out_redir));
	if (!redir)
		return (NULL);
	redir->out_mode = (*current)->type == REDIR_OUT ? 0 : 1;
	redir->out_file = NULL;
	redir->next = NULL;
	*current = (*current)->next;
	if (!*current || (*current)->type != WORD)
	{
		print_syntax_error("syntax error near unexpected token 'newline'");
		free(redir);
		return (NULL);
	}
	redir->out_file = ft_strdup((*current)->value);
	if (!redir->out_file)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

static void	append_in_redir(t_in_redir **head, t_in_redir *new)
{
	t_in_redir	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static void	append_out_redir(t_out_redir **head, t_out_redir *new)
{
	t_out_redir	*tmp;

	if (!*head)
		*head = new;
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	add_redirection_to_command(t_command *cmd, t_token **current)
{
	if ((*current)->type == REDIR_IN || (*current)->type == REDIR_HEREDOC)
	{
		t_in_redir *in = handle_in_redirection(current);
		if (!in)
			return (0);
		append_in_redir(&cmd->in_redir, in);
	}
	else if ((*current)->type == REDIR_OUT || (*current)->type == REDIR_APPEND)
	{
		t_out_redir *out = handle_out_redirection(current);
		if (!out)
			return (0);
		append_out_redir(&cmd->out_redir, out);
	}
	return (1);
}
