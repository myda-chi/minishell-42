#include "executor.h"
#include "utils.h"
#include <fcntl.h>

static char *create_temp_filename(int index)
{
    char *index_str;
    char *tmp_file;
    char *base_name;

    base_name = "/tmp/minishell_heredoc_";
    index_str = ft_itoa(index);
    if (!index_str)
        return (NULL);
    tmp_file = ft_strjoin(base_name, index_str);
    free(index_str);
    return (tmp_file);
}

static int create_temp_file(char *tmp_file)
{
    int fd;

    fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        perror("open");
        free(tmp_file);
        return (-1);
    }
    return (fd);
}

static void write_heredoc_content(int fd, char *delimiter)
{
    char *line;

    while (1)
    {
        line = readline("> ");
        if (!line)
            break;
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        ft_putendl_fd(line, fd);
        free(line);
    }
}

static int open_temp_for_reading(char *tmp_file)
{
    int fd;

    fd = open(tmp_file, O_RDONLY);
    unlink(tmp_file);
    free(tmp_file);
    return (fd);
}

int handle_heredoc(char *delimiter, int index)
{
    char *tmp_file;
    int fd;

    tmp_file = create_temp_filename(index);
    if (!tmp_file)
        return (-1);
    fd = create_temp_file(tmp_file);
    if (fd < 0)
        return (-1);
    write_heredoc_content(fd, delimiter);
    close(fd);
    return (open_temp_for_reading(tmp_file));
}
