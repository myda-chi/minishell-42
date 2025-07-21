/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_resolver.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 15:00:49 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/21 19:07:33 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include "utils.h"

static int	check_direct_access(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

static char	**get_path_directories(t_shell_state *state)
{
	char	*path_env;
	char	**paths;

	path_env = get_env_value_from_state(state, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (paths);
}

char	*build_command_path(char *dir, char *cmd)
{
	char	*path;
	char	*cmd_path;

	path = ft_strjoin(dir, "/");
	if (!path)
		return (NULL);
	cmd_path = ft_strjoin(path, cmd);
	free(path);
	return (cmd_path);
}

void	free_paths_array(char **paths, int start)
{
	while (paths[start])
	{
		free(paths[start]);
		start++;
	}
	free(paths);
}

char	*get_cmd_path(char **argv, t_shell_state *state)
{
	char	**paths;

	if (!argv || !argv[0])
		return (NULL);
	if (check_direct_access(argv[0]))
		return (ft_strdup(argv[0]));
	paths = get_path_directories(state);
	if (!paths)
		return (NULL);
	return (find_cmd_in_paths(paths, argv));
}
