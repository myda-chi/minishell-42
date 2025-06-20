#include "builtins.h"

int ft_exit(int argc, char **argv)
{
    if (argc > 2)
    {
        ft_putstr_fd("exit: too many arguments\n", 2);
        return (1);
    }
    if (argc == 2)
    {
        if (ft_str_is_numeric(argv[1]))
            exit(ft_atoi(argv[1]));
        else
        {
            ft_putstr_fd("exit: numeric argument required\n", 2);
            exit(255);
        }
    }
    exit(0);
} 