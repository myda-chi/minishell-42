#include "executor.h"
#include "utils.h"
#include <sys/wait.h>

static int create_pipe_if_needed(t_command *current, int *fd)
{
    if (current->next)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            return (-1);
        }
    }
    return (0);
}

static void setup_child_pipes(int in_fd, int *fd, t_command *current)
{
    if (in_fd != 0)
    {
        dup2(in_fd, 0);
        close(in_fd);
    }
    if (current->next)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
    }
}

static void cleanup_parent_pipes(int *in_fd, int *fd, t_command *current)
{
    if (*in_fd != 0)
        close(*in_fd);
    if (current->next)
    {
        *in_fd = fd[0];
        close(fd[1]);
    }
}

static void wait_for_all_children(t_shell_state *state)
{
    int status;

    while (wait(&status) > 0)
    {
        if (WIFEXITED(status))
            set_exit_status_in_state(state, WEXITSTATUS(status));
        else if (WIFSIGNALED(status))
        {
            if (WTERMSIG(status) == SIGINT)
                ft_putstr_fd("\n", 1);
            set_exit_status_in_state(state, 128 + WTERMSIG(status));
        }
    }
}

void execute_pipeline(t_command *commands, t_shell_state *state)
{
    int fd[2];
    pid_t pid;
    int in_fd;
    t_command *current;

    in_fd = 0;
    current = commands;
    init_signals_parent();
    while (current)
    {
        if (create_pipe_if_needed(current, fd) == -1)
        {
            set_exit_status_in_state(state, 1);
            return;
        }
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            set_exit_status_in_state(state, 1);
            return;
        }
        if (pid == 0)
        {   
            init_signals_child();
            setup_child_pipes(in_fd, fd, current);
            execute_simple_command(current, state);
            exit(get_exit_status_from_state(state));
        }
        cleanup_parent_pipes(&in_fd, fd, current);
        current = current->next;
    }
    wait_for_all_children(state);
    init_signals();
}
