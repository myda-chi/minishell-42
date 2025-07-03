#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int ft_echo(int argc, char **argv);
int ft_cd(int argc, char **argv, t_shell_state *state);
int ft_pwd(void);
int ft_export(int argc, char **argv, t_shell_state *state);
int ft_unset(int argc, char **argv, t_shell_state *state);
int ft_env(t_shell_state *state);
int ft_exit(int argc, char **argv, t_shell_state *state);

#endif 