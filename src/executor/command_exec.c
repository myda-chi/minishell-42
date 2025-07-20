/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:00:22 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/20 21:36:56 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"
#include <sys/wait.h>

static void handle_child_process(t_command *cmd, t_shell_state *state)
{
    int status;
    
    if (handle_redirections(cmd) == -1)
        exit(1);
    if (!cmd->argv)
    {
        status = 0;
        exit(status);
    }
    execute_external_command(cmd, state);
}

static void handle_parent_process(pid_t pid, t_shell_state *state)
{
    int status;

    waitpid(pid, &status, 0);

    if (WIFEXITED(status))
        set_exit_status_in_state(state, WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        set_exit_status_in_state(state, 128 + WTERMSIG(status));
}

static pid_t create_child_process(void)
{
    pid_t pid;

    pid = fork();
    if (pid == -1)
        perror("fork");
    return (pid);
}

void execute_simple_command(t_command *cmd, t_shell_state *state)
{
    pid_t pid;

    pid = create_child_process();
    if (pid == -1)
    {
        set_exit_status_in_state(state, 1);
        return ;
    }
    if (pid == 0)
        handle_child_process(cmd, state);
    else
        handle_parent_process(pid, state);
}
