#include "builtins.h"

static void remove_env_var(char *var, char ***envp)
{
    int i;
    int j;
    int len;
    int count;

    i = 0;
    count = 0;
    while ((*envp)[count])
        count++;
    len = ft_strlen(var);
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], var, len) == 0 && (*envp)[i][len] == '=')
        {
            free((*envp)[i]);
            j = i;
            while ((*envp)[j])
            {
                (*envp)[j] = (*envp)[j + 1];
                j++;
            }
            // realloc to smaller size
            return;
        }
        i++;
    }
}

int ft_unset(int argc, char **argv, char ***envp)
{
    int i;

    if (argc == 1)
        return (0);
    i = 1;
    while (i < argc)
    {
        remove_env_var(argv[i], envp);
        i++;
    }
    return (0);
} 