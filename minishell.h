#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#define R "\033[31m"
#define G  "\033[32m"
#define Y "\033[33m"
#define B   "\033[34m"

typedef struct s_in_redir
{
	char    *delimeter; 
	char    *in_file;   
	int     in_mode;      // if 0 equals <, if 1 equals heredoc, -1 for no file
	int     in_fd;
	struct s_in_redir    *next;
}t_in_redir;

typedef struct s_out_redir
{
	char    			*out_file;    // if 0 equals <, if 1 equals heredoc, -1 for no file
	int     			out_mode;
	int					out_fd;
	struct s_out_redir	*next;
}   t_out_redir;

typedef enum s_cmd_type
{
	COMMAND,
	PIPES
}   t_cmd_type;

typedef struct s_command
{
	t_cmd_type          type;
	t_in_redir          *in_redir;
	t_out_redir         *out_redir;
	char                **argv;
	int                 argc;
	struct s_command    *next;   
}	t_command;

// t_command *parse_commands(char *line);

#endif