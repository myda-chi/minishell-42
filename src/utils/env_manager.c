#include "utils.h"

/* Shell State Management */
t_shell_state *init_shell_state(char **envp)
{
	t_shell_state *state;
	char *pid_str;

	state = malloc(sizeof(t_shell_state));
	if (!state)
		return (NULL);
	
	state->env_table = load_env_from_array(envp);
	if (!state->env_table)
	{
		free(state);
		return (NULL);
	}
	
	state->exit_status = 0;
	state->shell_pid = getpid();
	
	/* Set default shell variables */
	set_env_value_in_state(state, "?", "0");
	pid_str = ft_itoa(state->shell_pid);
	if (pid_str)
	{
		set_env_value_in_state(state, "$", pid_str);
		free(pid_str);
	}
	
	return (state);
}

void cleanup_shell_state(t_shell_state *state)
{
	if (!state)
		return;
	if (state->env_table)
		free_env_table(state->env_table);
	free(state);
}

/* State-based Environment Management */
char *get_env_value_from_state(t_shell_state *state, const char *key)
{
	if (!state || !state->env_table)
		return (NULL);
	return (env_get(state->env_table, key));
}

int set_env_value_in_state(t_shell_state *state, const char *key, const char *value)
{
	if (!state || !state->env_table)
		return (0);
	return (env_set(state->env_table, key, value));
}

int unset_env_value_from_state(t_shell_state *state, const char *key)
{
	if (!state || !state->env_table)
		return (0);
	return (env_unset(state->env_table, key));
}

char **get_env_array_from_state(t_shell_state *state)
{
	if (!state || !state->env_table)
		return (NULL);
	return (env_table_to_array(state->env_table));
}

void set_exit_status_in_state(t_shell_state *state, int status)
{
	char *status_str;

	if (!state)
		return;
	
	state->exit_status = status;
	status_str = ft_itoa(status);
	if (status_str)
	{
		set_env_value_in_state(state, "?", status_str);
		free(status_str);
	}
}

int get_exit_status_from_state(t_shell_state *state)
{
	if (!state)
		return (0);
	return (state->exit_status);
}

void free_env_array(char **env_array)
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
