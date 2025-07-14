/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:40:13 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 21:40:23 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "utils.h"

static void	print_env_array(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], 1);
		i++;
	}
}

int	ft_env(t_shell_state *state)
{
	char	**envp;

	envp = get_env_array_from_state(state);
	if (!envp)
		return (1);
	print_env_array(envp);
	free_env_array(envp);
	return (0);
}
