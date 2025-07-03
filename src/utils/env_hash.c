#include "utils.h"

#define HASH_TABLE_SIZE 256

static unsigned int hash_function(const char *key)
{
	unsigned int hash;
	int i;

	hash = 5381;
	i = 0;
	while (key[i])
	{
		hash = ((hash << 5) + hash) + key[i];
		i++;
	}
	return (hash % HASH_TABLE_SIZE);
}

t_env_table *init_env_table(void)
{
	t_env_table *table;
	int i;

	table = malloc(sizeof(t_env_table));
	if (!table)
		return (NULL);
	table->buckets = malloc(sizeof(t_env_var *) * HASH_TABLE_SIZE);
	if (!table->buckets)
	{
		free(table);
		return (NULL);
	}
	i = 0;
	while (i < HASH_TABLE_SIZE)
	{
		table->buckets[i] = NULL;
		i++;
	}
	table->size = HASH_TABLE_SIZE;
	return (table);
}

t_env_var *create_env_var(const char *key, const char *value)
{
	t_env_var *var;

	var = malloc(sizeof(t_env_var));
	if (!var)
		return (NULL);
	var->key = ft_strdup(key);
	var->value = ft_strdup(value);
	if (!var->key || !var->value)
	{
		free(var->key);
		free(var->value);
		free(var);
		return (NULL);
	}
	var->next = NULL;
	return (var);
}

int env_set(t_env_table *table, const char *key, const char *value)
{
	unsigned int index;
	t_env_var *current;
	t_env_var *new_var;

	if (!table || !key)
		return (0);
	index = hash_function(key);
	current = table->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value ? value : "");
			return (current->value != NULL);
		}
		current = current->next;
	}
	new_var = create_env_var(key, value ? value : "");
	if (!new_var)
		return (0);
	new_var->next = table->buckets[index];
	table->buckets[index] = new_var;
	return (1);
}

char *env_get(t_env_table *table, const char *key)
{
	unsigned int index;
	t_env_var *current;

	if (!table || !key)
		return (NULL);
	index = hash_function(key);
	current = table->buckets[index];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int env_unset(t_env_table *table, const char *key)
{
	unsigned int index;
	t_env_var *current;
	t_env_var *prev;

	if (!table || !key)
		return (0);
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

void free_env_table(t_env_table *table)
{
	t_env_var *current;
	t_env_var *next;
	int i;

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

t_env_table *load_env_from_array(char **envp)
{
	t_env_table *table;
	char *key;
	char *value;
	char *eq_pos;
	int i;

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

static int count_env_vars(t_env_table *table)
{
	int count;
	int i;
	t_env_var *current;

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
	char **envp;
	char *env_str;
	int count;
	int idx;
	int i;
	t_env_var *current;

	if (!table)
		return (NULL);
	count = count_env_vars(table);
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	idx = 0;
	i = 0;
	while (i < table->size)
	{
		current = table->buckets[i];
		while (current)
		{
			env_str = ft_strjoin(current->key, "=");
			if (env_str)
			{
				envp[idx] = ft_strjoin(env_str, current->value);
				free(env_str);
				if (envp[idx])
					idx++;
			}
			current = current->next;
		}
		i++;
	}
	envp[idx] = NULL;
	return (envp);
}
