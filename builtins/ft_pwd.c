#include "builtins.h"

int ft_pwd(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        ft_putendl_fd(cwd, 1);
        return (0);
    }
    else
    {
        perror("pwd");
        return (1);
    }
} 