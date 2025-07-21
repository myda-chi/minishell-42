/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:01:13 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/21 20:04:40 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <fcntl.h>

int	my_dup2(int fd1, int fd2)
{
	if (dup2(fd1, fd2) == -1)
	{
		perror("dup2");
		return (-1);
	}
	return (0);
}

static int	process_input_redirection(t_in_redir *in)
{
	if (!in)
		return (0);
	while (in)
	{
		if (in->in_mode == 0)
			in->in_fd = open(in->in_file, O_RDONLY, 0644);
		else if (in->in_mode == 1)
			in->in_fd = handle_heredoc(in->delimeter, 0);
		else
			in->in_fd = STDIN_FILENO;
		if (in->in_fd < 0)
			return (-1);
		if (in->next == NULL)
			break ;
		close(in->in_fd);
		in = in->next;
	}
	if (my_dup2(in->in_fd, STDIN_FILENO) != 0)
		return (-1);
	return (0);
}

static int	process_output_redirection(t_out_redir *out)
{
	if (!out)
		return (0);
	while (out)
	{
		if (out->out_mode == 0)
			out->out_fd = open(out->out_file, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (out->out_mode == 1)
			out->out_fd = open(out->out_file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			out->out_fd = STDOUT_FILENO;
		if (out->out_fd < 0)
			return (perror("open"), -1);
		if (out->next == NULL)
			break ;
		close(out->out_fd);
		out = out->next;
	}
	if (my_dup2(out->out_fd, STDOUT_FILENO) != 0)
		return (-1);
	return (0);
}

int	handle_redirections(t_command *cmd)
{
	t_out_redir	*out;
	t_in_redir	*in;

	if (!cmd)
		return (-1);
	out = cmd->out_redir;
	in = cmd->in_redir;
	if (process_input_redirection(in) < 0)
		return (-1);
	if (process_output_redirection(out) < 0)
		return (-1);
	return (0);
}

void	execute_pipeline(t_command *commands, t_shell_state *state)
{
	int			fd[2];
	int			in_fd;
	t_command	*current;

	in_fd = 0;
	current = commands;
	init_signals_parent();
	while (current)
	{
		if (launch_child_and_manage_pipe(current, state, &in_fd, fd) == -1)
			return ;
		current = current->next;
	}
	wait_for_all_children(state);
	init_signals();
}
