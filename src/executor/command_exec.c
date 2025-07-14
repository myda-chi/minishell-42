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
    if (is_builtin(cmd->argv[0]))
    {
        status = execute_builtin(cmd, state);
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
