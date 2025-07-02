#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"

/* Main execution function */
void execute(t_command *commands, t_shell_state *state);

/* Redirection handling */
int handle_redirections(t_command *cmd);
int handle_heredoc(char *delimiter, int index);

/* Builtin functions */
int is_builtin(const char *cmd);
int execute_builtin(t_command *cmd, t_shell_state *state);

/* Command execution */
void execute_simple_command(t_command *cmd, t_shell_state *state);
void execute_external_command(t_command *cmd, t_shell_state *state);
void execute_pipeline(t_command *commands, t_shell_state *state);

/* Path resolution */
char *get_cmd_path(char **argv, t_shell_state *state);

#endif 