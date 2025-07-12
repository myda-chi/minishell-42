#include "utils.h"

/* Core Environment State Operations */
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
