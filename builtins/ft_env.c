#include "builtins.h"

int ft_env(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        ft_putendl_fd(envp[i], 1);
        i++;
    }
    return (0);
} 