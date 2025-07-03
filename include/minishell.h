#ifndef MINISHELL_H
# define MINISHELL_H

/* Standard C Libraries */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>
# include <stdbool.h>
# include <termios.h>
# include <dirent.h>
# include <ctype.h>

/* External Libraries */
# include <readline/readline.h>
# include <readline/history.h>

/* Project Libraries */
# include "../libft/libft.h"

/* Forward Declarations */
typedef struct s_env_var t_env_var;
typedef struct s_env_table t_env_table;

/* Shell State Structure */
typedef struct s_shell_state
{
	t_env_table	*env_table;
	int			exit_status;
	pid_t		shell_pid;
}	t_shell_state;

/* Color Codes */
# define R "\033[31m"
# define G "\033[32m"
# define Y "\033[33m"
# define B "\033[34m"

/* Data Structures */
typedef struct s_in_redir
{
	char    			*delimeter; 
	char    			*in_file;   
	int     			in_mode;      // 0 = <, 1 = <<
	int     			in_fd;
	struct s_in_redir   *next;
}	t_in_redir;

typedef struct s_out_redir
{
	char    			*out_file;
	int     			out_mode;     // 0 = >, 1 = >>
	int					out_fd;
	struct s_out_redir	*next;
}	t_out_redir;

typedef struct s_command
{
	t_in_redir          *in_redir;
	t_out_redir         *out_redir;
	char                **argv;
	int                 argc;
	struct s_command    *next;   
}	t_command;

/* Forward Declarations */
t_command	*parse_command(char *input, t_shell_state *state);
void		execute(t_command *commands, t_shell_state *state);
void		free_commands(t_command *commands);

/* Shell State Management */
t_shell_state	*init_shell_state(char **envp);
void			cleanup_shell_state(t_shell_state *state);

#endif