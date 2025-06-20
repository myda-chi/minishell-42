#include "builtins.h"
#include "utils.h"

static void print_env_sorted(char **envp)
{
    int i;
    int count;
    char **sorted_env;

    count = 0;
    while(envp[count])
        count++;
    sorted_env = malloc(sizeof(char *) * (count + 1));
    if (!sorted_env)
        return;
    i = 0;
    while (i < count)
    {
        sorted_env[i] = envp[i];
        i++;
    }
    sorted_env[i] = NULL;
    // a bubble sort for the env
    // ...
    i = 0;
    while (sorted_env[i])
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(sorted_env[i], 1);
        i++;
    }
    free(sorted_env);
}

int ft_export(int argc, char **argv, char ***my_envp)
{
    int i;
    char *p;

    if (argc == 1)
    {
        print_env_sorted(*my_envp);
        return (0);
    }
    i = 1;
    while (i < argc)
    {
        p = ft_strchr(argv[i], '=');
        if (p)
        {
            *p = '\0';
            set_env_var(argv[i], p + 1, my_envp);
            *p = '=';
        }
        i++;
    }
    return (0);
} 