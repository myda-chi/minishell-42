/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:01:59 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/28 20:00:42 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "minishell.h"
#include "parser.h"
#include "utils.h"

void	increment_shell_level(t_shell_state *state)
{
	char	*current_level;
	char	*new_level_str;
	int		current_level_int;
	int		new_level;

	if (!state)
		return ;
	current_level = get_env_value_from_state(state, "SHLVL");
	if (!current_level)
		current_level_int = 0;
	else
		current_level_int = ft_atoi(current_level);
	new_level = current_level_int + 1;
	new_level_str = ft_itoa(new_level);
	if (new_level_str)
	{
		set_env_value_in_state(state, "SHLVL", new_level_str);
		free(new_level_str);
	}
}

static int	is_only_whitespace(char *str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
            return (0);
        i++;
    }
    return (1);
}

static void	run_shell_loop(t_shell_state *state)
{
	char		*input;
	t_command	*cmd;

	while (1)
	{
		input = readline("🤖 minishell➤ ");
		if (!input)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (ft_strlen(input) > 0 && !is_only_whitespace(input))
		{
			add_history(input);
			cmd = parse_command(input, state);
			if (cmd)
			{
				execute(cmd, state);
				free_commands(cmd);
			}
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell_state	*state;
	int				exit_status;

	(void)argc;
	(void)argv;
	state = init_shell_state(envp);
	increment_shell_level(state);
	if (!state)
	{
		ft_putstr_fd("minishell: failed to initialize shell state\n", 2);
		return (1);
	}
	init_signals();
	disable_echoctl();
	run_shell_loop(state);
	exit_status = get_exit_status_from_state(state);
	cleanup_shell_state(state);
	return (exit_status);
}
