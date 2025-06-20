#include "executor.h"
#include "builtins.h"
#include <sys/wait.h>
#include <fcntl.h>

static int handle_heredoc(char *delimiter)
{
    char *line;
    int fd;
    char *tmp_file = "/tmp/minishell_heredoc";

    fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        return (-1);
    }
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd);
        free(line);
    }
    close(fd);
    fd = open(tmp_file, O_RDONLY);
    unlink(tmp_file);
    return (fd);
}

void handle_redirections(t_command *cmd)
{
    t_in_redir *in;
    t_out_redir *out;
    int fd;

    in = cmd->in_redir;
    out = cmd->out_redir;
    while (in)
    {
        if (in->in_mode == 0) // <
            fd = open(in->in_file, O_RDONLY);
        else // <<
            fd = handle_heredoc(in->delimeter);
        if (fd < 0)
        {
            perror("open"); // handle error
            return;
        }
        dup2(fd, 0);
        close(fd);
        in = in->next;
    }
    while (out)
    {
        if (out->out_mode == 0) // >
            fd = open(out->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        else // >>
            fd = open(out->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
            perror("open"); // handle error
        dup2(fd, 1);
        close(fd);
        out = out->next;
    }
}

static int execute_builtin(t_command *cmd, char ***envp)
{
    if (ft_strcmp(cmd->argv[0], "echo") == 0)
        return (ft_echo(cmd->argc, cmd->argv));
    if (ft_strcmp(cmd->argv[0], "cd") == 0)
        return (ft_cd(cmd->argc, cmd->argv, envp));
    if (ft_strcmp(cmd->argv[0], "pwd") == 0)
        return (ft_pwd());
    if (ft_strcmp(cmd->argv[0], "export") == 0)
        return (ft_export(cmd->argc, cmd->argv, envp));
    if (ft_strcmp(cmd->argv[0], "unset") == 0)
        return (ft_unset(cmd->argc, cmd->argv, envp));
    if (ft_strcmp(cmd->argv[0], "env") == 0)
        return (ft_env(*envp));
    if (ft_strcmp(cmd->argv[0], "exit") == 0)
        return (ft_exit(cmd->argc, cmd->argv));
    return (-1);
}

static char *get_cmd_path(char *cmd, char **envp)
{
    char    **paths;
    char    *path;
    char    *cmd_path;
    int     i;

    if (access(cmd, F_OK | X_OK) == 0)
        return (ft_strdup(cmd));
    while (*envp && ft_strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    if (!*envp)
        return (NULL);
    paths = ft_split((*envp) + 5, ':');
    i = 0;
    while (paths[i])
    {
        path = ft_strjoin(paths[i], "/");
        cmd_path = ft_strjoin(path, cmd);
        free(path);
        if (access(cmd_path, F_OK | X_OK) == 0)
        {
            // free paths
            return (cmd_path);
        }
        free(cmd_path);
        i++;
    }
    // free paths
    return (NULL);
}

static void execute_simple_command(t_command *cmd, char ***envp)
{
    pid_t   pid;
    char    *cmd_path;
    int     status;

    status = execute_builtin(cmd, envp);
    if (status != -1)
        return; // handle exit status
    
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        return;
    }
    if (pid == 0)
    {
        handle_redirections(cmd);
        cmd_path = get_cmd_path(cmd->argv[0], *envp);
        if (!cmd_path)
        {
            // print error
            exit(127);
        }
        execve(cmd_path, cmd->argv, *envp);
        // print error
        exit(126);
    }
    else
    {
        waitpid(pid, &status, 0);
        // handle exit status
    }
}

void execute(t_command *commands, char ***envp)
{
    int fd[2];
    pid_t pid;
    int in_fd;

    in_fd = 0;
    while (commands)
    {
        if (commands->next)
            pipe(fd);
        pid = fork();
        if (pid == 0)
        {
            if (in_fd != 0)
            {
                dup2(in_fd, 0);
                close(in_fd);
            }
            if (commands->next)
            {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
            }
            execute_simple_command(commands, envp);
            exit(0);
        }
        if (in_fd != 0)
            close(in_fd);
        if (commands->next)
        {
            in_fd = fd[0];
            close(fd[1]);
        }
        commands = commands->next;
    }
    while (wait(NULL) > 0);
} 