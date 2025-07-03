#include "parser.h"

void print_syntax_error(char *error)
{
    ft_putstr_fd("minishell: ", 2);
    ft_putstr_fd(error, 2);
    ft_putstr_fd("\n", 2);
} 