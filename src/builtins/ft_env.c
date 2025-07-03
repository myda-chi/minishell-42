#include "builtins.h"
#include "utils.h"

static void print_env_array(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
}

int ft_env(t_shell_state *state)
{
    char **envp;

    envp = get_env_array_from_state(state);
    if (!envp)
        return (1);
    print_env_array(envp);
    free_env_array(envp);
    return (0);
} 