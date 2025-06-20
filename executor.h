#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"

void execute(t_command *commands, char ***envp);
void handle_redirections(t_command *cmd);

#endif 