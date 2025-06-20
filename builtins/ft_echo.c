#include "builtins.h"

int ft_echo(int argc, char **argv)
{
    int i;
    int n_flag;

    i = 1;
    n_flag = 0;
    if (argc > 1 && ft_strcmp(argv[1], "-n") == 0)
    {
        n_flag = 1;
        i++;
    }
    while (i < argc)
    {
        ft_putstr_fd(argv[i], 1);
        if (i < argc - 1)
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (!n_flag)
        ft_putstr_fd("\n", 1);
    return (0);
} 