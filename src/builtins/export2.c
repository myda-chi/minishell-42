/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:39:45 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/13 22:00:09 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

char	**create_env_copy(char **envp, int count)
{
	char	**sorted_env;
	int		i;

	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (NULL);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = envp[i];
		i++;
	}
	sorted_env[count] = NULL;
	return (sorted_env);
}

void	print_declare_format(char **sorted_env, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(sorted_env[i], 1);
		free(sorted_env[i]);
		i++;
	}
}

int	validate_export_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	sort_env_array(char **env_array, int count)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - 1 - i)
		{
			if (ft_strcmp(env_array[j], env_array[j + 1]) > 0)
			{
				temp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}
