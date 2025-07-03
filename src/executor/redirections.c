#include "executor.h"
#include <fcntl.h>

static int handle_input_redirection(t_in_redir *in, int index)
{
    int fd;

    if (in->in_mode == 0)
        fd = open(in->in_file, O_RDONLY);
    else
        fd = handle_heredoc(in->delimeter, index);
    if (fd < 0)
    {
        perror("minishell");
        return (-1);
    }
    dup2(fd, 0);
    close(fd);
    return (0);
}

static t_out_redir *find_last_output(t_out_redir *out)
{
    t_out_redir *last_out;

    last_out = NULL;
    if (out)
    {
        last_out = out;
        while (last_out->next)
            last_out = last_out->next;
    }
    return (last_out);
}

static int handle_output_redirection(t_out_redir *out, t_out_redir *last)
{
    int fd;

    if (out->out_mode == 0)
        fd = open(out->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else
        fd = open(out->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd < 0)
    {
        perror("minishell");
        return (-1);
    }
    if (out == last)
        dup2(fd, 1);
    close(fd);
    return (0);
}

static int process_input_redirections(t_command *cmd)
{
    t_in_redir *in;
    int heredoc_index;

    in = cmd->in_redir;
    heredoc_index = 0;
    while (in)
    {
        if (handle_input_redirection(in, heredoc_index) == -1)
            return (-1);
        heredoc_index++;
        in = in->next;
    }
    return (0);
}

int handle_redirections(t_command *cmd)
{
    t_out_redir *out;
    t_out_redir *last_out;

    if (process_input_redirections(cmd) == -1)
        return (-1);
    out = cmd->out_redir;
    last_out = find_last_output(out);
    while (out)
    {
        if (handle_output_redirection(out, last_out) == -1)
            return (-1);
        out = out->next;
    }
    return (0);
}
