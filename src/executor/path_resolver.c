#include "executor.h"
#include "utils.h"

static int check_direct_access(char *cmd)
{
    if (access(cmd, F_OK | X_OK) == 0)
        return (1);
    return (0);
}

static char **get_path_directories(t_shell_state *state)
{
    char *path_env;
    char **paths;

    path_env = get_env_value_from_state(state, "PATH");
    if (!path_env)
        return (NULL);
    paths = ft_split(path_env, ':');
    return (paths);
}

static char *build_command_path(char *dir, char *cmd)
{
    char *path;
    char *cmd_path;

    path = ft_strjoin(dir, "/");
    if (!path)
        return (NULL);
    cmd_path = ft_strjoin(path, cmd);
    free(path);
    return (cmd_path);
}

static void free_paths_array(char **paths, int start)
{
    while (paths[start])
    {
        free(paths[start]);
        start++;
    }
    free(paths);
}

char *get_cmd_path(char **argv, t_shell_state *state)
{
    char **paths;
    char *cmd_path;
    int i;

    if (!argv || !argv[0])
        return (NULL);
    if (check_direct_access(argv[0]))
        return (ft_strdup(argv[0]));
    paths = get_path_directories(state);
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        cmd_path = build_command_path(paths[i], argv[0]);
        if (cmd_path && access(cmd_path, F_OK | X_OK) == 0)
        {
            free_paths_array(paths, i);
            free(argv[0]);
            argv[0] = cmd_path;
            return (ft_strdup(cmd_path));
        }
        free(cmd_path);
        free(paths[i]);
        i++;
    }
    free(paths);
    return (NULL);
}
