#include "parser.h"

static void	free_in_redirections(t_in_redir *redir)
{
	t_in_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->delimeter)
			free(redir->delimeter);
		if (redir->in_file)
			free(redir->in_file);
		free(redir);
		redir = next;
	}
}

static void	free_out_redirections(t_out_redir *redir)
{
	t_out_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->out_file)
			free(redir->out_file);
		free(redir);
		redir = next;
	}
}

void	free_command(t_command *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->argv)
	{
		i = 0;
		while (cmd->argv[i])
			free(cmd->argv[i++]);
		free(cmd->argv);
	}
	free_in_redirections(cmd->in_redir);
	free_out_redirections(cmd->out_redir);
	free(cmd);
}

void	free_commands(t_command *commands)
{
	t_command	*next;

	while (commands)
	{
		next = commands->next;
		free_command(commands);
		commands = next;
	}
}
