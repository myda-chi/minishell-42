#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/* Environment Hash Table Structures */
typedef struct s_env_var
{
	char				*key;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct s_env_table
{
	t_env_var	**buckets;
	int			size;
}	t_env_table;

/* Environment Hash Table Functions */
t_env_table	*init_env_table(void);
int			env_set(t_env_table *table, const char *key, const char *value);
char		*env_get(t_env_table *table, const char *key);
int			env_unset(t_env_table *table, const char *key);
void		free_env_table(t_env_table *table);
t_env_table	*load_env_from_array(char **envp);
char		**env_table_to_array(t_env_table *table);

/* Shell State Environment Management */
char		*get_env_value_from_state(t_shell_state *state, const char *key);
int			set_env_value_in_state(t_shell_state *state, const char *key, const char *value);
int			unset_env_value_from_state(t_shell_state *state, const char *key);
char		**get_env_array_from_state(t_shell_state *state);
void		free_env_array(char **env_array);
void		set_exit_status_in_state(t_shell_state *state, int status);
int			get_exit_status_from_state(t_shell_state *state);

/* String Utilities */
int		ft_str_is_numeric(char *str);

/* Variable Expansion */
char	*expand_variables(char *str, t_shell_state *state);
char *remove_quotes(const char *str);

/* Prompt Functions */
void	dig_prompt(void);

#endif