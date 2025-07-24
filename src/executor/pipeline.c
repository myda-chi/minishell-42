/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 20:22:18 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/24 20:22:37 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "utils.h"

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
