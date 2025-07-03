#include "parser.h"
#include "utils.h"

int	count_word_tokens(t_token *tokens)
{
	int count;

	count = 0;
	while (tokens && tokens->type != PIPE && tokens->type != END)
	{
		if (tokens->type == WORD)
			count++;
		else if (tokens->type >= REDIR_IN && tokens->type <= REDIR_HEREDOC)
		{
			tokens = tokens->next;
			if (tokens && tokens->type == WORD)
				tokens = tokens->next;
			continue;
		}
		tokens = tokens->next;
	}
	return (count);
}

t_command *init_command(int argc)
{
	t_command *cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->argc = argc;
	if (argc > 0)
	{
		cmd->argv = ft_calloc(argc + 1, sizeof(char *));
		if (!cmd->argv)
		{
			free(cmd);
			return (NULL);
		}
	}
	return (cmd);
}

t_command *build_simple_command(t_token **current, t_shell_state *state)
{
	t_command	*cmd;
	int			argc;
	int			i;
	char		*unquoted;

	if (!current || !*current)
		return (NULL);
	argc = count_word_tokens(*current);
	cmd = init_command(argc);
	if (!cmd)
		return (NULL);
	i = 0;
	while (*current && (*current)->type != PIPE && (*current)->type != END)
	{
		if ((*current)->type == WORD)
		{
			char *expanded = expand_variables((*current)->value, state);
			if (expanded)
			{
				unquoted = remove_quotes(expanded);
				free(expanded);
				if(unquoted)
					cmd->argv[i++] = unquoted;
				else
					cmd->argv[i++] = ft_strdup((*current)->value);
			}
			else
				cmd->argv[i++] = ft_strdup((*current)->value);
		}
		else if ((*current)->type >= REDIR_IN && (*current)->type <= REDIR_HEREDOC)
		{
			if (!add_redirection_to_command(cmd, current))
			{
				free_command(cmd);
				return (NULL);
			}
		}
		*current = (*current)->next;
	}
	return (cmd);
}
