#include "utils.h"

/* Exit Status Management */
void set_exit_status_in_state(t_shell_state *state, int status)
{
	char *status_str;

	if (!state)
		return;
	state->exit_status = status;
	status_str = ft_itoa(status);
	if (status_str)
	{
		env_set(state->env_table, "?", status_str);
		free(status_str);
	}
}

int get_exit_status_from_state(t_shell_state *state)
{
	if (!state)
		return (0);
	return (state->exit_status);
}
