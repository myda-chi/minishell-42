/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myda-chi <myda-chi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 19:49:33 by myda-chi          #+#    #+#             */
/*   Updated: 2025/07/12 21:14:59 by myda-chi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	env_unset(t_env_table *table, const char *key)
{
	unsigned int	index;
	t_env_var		*current;
	t_env_var		*prev;

	if (!table || !key) return (0);
	index = hash_function(key);
	current = table->buckets[index];
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				table->buckets[index] = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

void	free_env_table(t_env_table *table)
{
	t_env_var	*current;
	t_env_var	*next;
	int			i;

	if (!table)
		return ;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			current = next;
		}
		i++;
	}
	free(table->buckets);
	free(table);
}

t_env_table	*load_env_from_array(char **envp)
{
	t_env_table	*table;
	char		*key;
	char		*value;
	char		*eq_pos;
	int			i;

	table = init_env_table();
	if (!table)
		return (NULL);
	i = 0;
	while (envp && envp[i])
	{
		eq_pos = ft_strchr(envp[i], '=');
		if (eq_pos)
		{
			key = ft_substr(envp[i], 0, eq_pos - envp[i]);
			value = ft_strdup(eq_pos + 1);
			if (key && value)
				env_set(table, key, value);
			free(key);
			free(value);
		}
		i++;
	}
	return (table);
}

static int	count_env_vars(t_env_table *table)
{
	int			count;
	int			i;
	t_env_var	*current;

	count = 0;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			count++;
			current = current->next;
		}
		i++;
	}
	return (count);
}

char **env_table_to_array(t_env_table *table)
{
    char    **envp;
    int     count;

    if (!table)
        return (NULL);
    count = count_env_vars(table);
    envp = malloc(sizeof(char *) * (count + 1));
    if (!envp)
        return (NULL);
    fill_env_array(table, envp);
    return (envp);
}
