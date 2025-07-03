#include "builtins.h"
#include "utils.h"

static void exit_with_status(t_shell_state *state, int status)
{
    set_exit_status_in_state(state, status);
    exit(status);
}

static void exit_numeric_error(t_shell_state *state)
{
    ft_putstr_fd("exit: numeric argument required\n", 2);
    exit_with_status(state, 255);
}

static void exit_too_many_args(void)
{
    ft_putstr_fd("exit: too many arguments\n", 2);
}

static int handle_numeric_argument(char *arg, t_shell_state *state)
{
    int exit_code;

    if (ft_str_is_numeric(arg))
    {
        exit_code = ft_atoi(arg);
        exit_with_status(state, exit_code);
    }
    else
    {
        exit_numeric_error(state);
    }
    return (0);
}

int ft_exit(int argc, char **argv, t_shell_state *state)
{
    if (argc > 2)
    {
        exit_too_many_args();
        return (1);
    }
    if (argc == 2)
        return (handle_numeric_argument(argv[1], state));
    exit_with_status(state, 0);
    return (0);
} 