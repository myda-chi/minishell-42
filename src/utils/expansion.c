#include "utils.h"

static char *expand_variable(const char *var_name, t_shell_state *state)
{
	char *value;

	if (!var_name || !state)
		return (ft_strdup(""));
	
	/* Handle special variables */
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(get_exit_status_from_state(state)));
	if (ft_strcmp(var_name, "$") == 0)
		return (ft_itoa(state->shell_pid));
	
	/* Handle regular environment variables */
	value = get_env_value_from_state(state, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static char *extract_var_name(const char *str, int *len)
{
	int i;

	i = 0;
	if (str[i] == '{')
	{
		i++;
		while (str[i] && str[i] != '}')
			i++;
		if (str[i] == '}')
		{
			*len = i + 1;
			return (ft_substr(str, 1, i - 1));
		}
	}
	else
	{
		while (str[i] && (ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?'))
			i++;
		*len = i;
		return (ft_substr(str, 0, i));
	}
	*len = 1;
	return (ft_strdup(""));
}

static char *expand_single_variable(const char *str, int start, int *new_len, t_shell_state *state)
{
	char *var_name;
	char *expanded;
	int var_len;

	var_name = extract_var_name(str + start + 1, &var_len);
	if (!var_name)
		return (NULL);
	
	expanded = expand_variable(var_name, state);
	// printf("hello: %d\n", (int)ft_strlen(expanded));
	free(var_name);
	
	if (!expanded)
		return (NULL);
	
	*new_len = var_len + 1; /* +1 for the $ */
	return (expanded);
}

char *expand_variables(char *str, t_shell_state *state)
{
	char *result;
	char *temp;
	char *expanded;
	int i;
	int var_len;

	if (!str)
		return (NULL);
	if (str[0] == '\'')
		return (ft_strdup(str));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && 
			(ft_isalnum(str[i + 1]) || str[i + 1] == '_' || 
			 str[i + 1] == '?' || str[i + 1] == '{'))
		{
			expanded = expand_single_variable(str, i, &var_len, state);
			if (expanded)
			{
				temp = ft_strjoin(result, expanded);
				free(result);
				free(expanded);
				result = temp;
				if (!result)
					return (NULL);
			}
			i += var_len;
		}
		else
		{
			temp = ft_substr(str, i, 1);
			if (temp)
			{
				expanded = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = expanded;
				if (!result)
					return (NULL); 
			}
			i++;
		}
	}
	return (result);
}
char *remove_quotes(const char *str)
{
    char *result;
    int i;
    int j;
    int quote_char;
    int in_dquotes;

    if (!str)
        return (NULL);

    result = malloc(sizeof(char) * (strlen(str) + 1));
    if (!result)
        return (NULL);

    i = 0;
    j = 0;
    in_dquotes = 0;
    quote_char = 0;

    while (str[i])
    {
        if (str[i] == '\'' && !in_dquotes)
        {
			quote_char = !quote_char;
			i++;
			continue;
        }
        else if (str[i] == '\"' && !quote_char)
        {
			in_dquotes = !in_dquotes;
			i++;
            continue;
        }
    	result[j++] = str[i++];
    }
    result[j] = '\0';
    return (result);
}
