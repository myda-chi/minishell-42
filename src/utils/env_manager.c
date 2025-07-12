#include "utils.h"

/* 1. Shell State Initialization */
t_shell_state *init_shell_state(char **envp)
{
	t_shell_state *state;
	char *pid_str;

	state = malloc(sizeof(t_shell_state));
	if (!state)
		return (NULL);
	state->env_table = load_env_from_array(envp);
	if (!state->env_table)
		return (free(state), NULL);
	state->exit_status = 0;
	state->shell_pid = getpid();
	pid_str = ft_itoa(state->shell_pid);
	if (pid_str)
		env_set(state->env_table, "$", pid_str), free(pid_str);
	env_set(state->env_table, "?", "0");
	return (state);
}

/* 2. Shell State Cleanup */
void cleanup_shell_state(t_shell_state *state)
{
	if (!state)
		return;
	if (state->env_table)
		free_env_table(state->env_table);
	free(state);
}

/* 3. Environment Variable Operations */
void *env_var_operation(t_shell_state *state, const char *key, 
						const char *value, int op_type)
{
	if (!state || !state->env_table)
		return (NULL);
	if (op_type == 0)  // GET
		return (env_get(state->env_table, key));
	else if (op_type == 1 && value)  // SET
		return ((void *)(long)env_set(state->env_table, key, value));
	else if (op_type == 2)  // UNSET
		return ((void *)(long)env_unset(state->env_table, key));
	else if (op_type == 3)  // GET_ARRAY
		return (env_table_to_array(state->env_table));
	return (NULL);
}

/* 4. Exit Status Operations */
int exit_status_operation(t_shell_state *state, int status, int op_type)
{
	char *status_str;

	if (!state)
		return (0);
	if (op_type == 0)  // SET_STATUS
	{
		state->exit_status = status;
		status_str = ft_itoa(status);
		if (status_str)
		{
			env_set(state->env_table, "?", status_str);
			free(status_str);
		}
		return (1);
	}
	return (state->exit_status);  // GET_STATUS
}

/* 5. Array Memory Management */
void array_memory_manager(char **env_array)
{
	int i;

	if (!env_array)
		return;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

/* Legacy API Functions - Wrappers for the 5 core functions */
char *get_env_value_from_state(t_shell_state *state, const char *key)
{
	return ((char *)env_var_operation(state, key, NULL, 0));
}

int set_env_value_in_state(t_shell_state *state, const char *key, const char *value)
{
	return ((int)(long)env_var_operation(state, key, value, 1));
}

int unset_env_value_from_state(t_shell_state *state, const char *key)
{
	return ((int)(long)env_var_operation(state, key, NULL, 2));
}

char **get_env_array_from_state(t_shell_state *state)
{
	return ((char **)env_var_operation(state, NULL, NULL, 3));
}

void set_exit_status_in_state(t_shell_state *state, int status)
{
	exit_status_operation(state, status, 0);
}

int get_exit_status_from_state(t_shell_state *state)
{
	return (exit_status_operation(state, 0, 1));
}

void free_env_array(char **env_array)
{
	array_memory_manager(env_array);
}
