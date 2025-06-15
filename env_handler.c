#include "parser.h"

static int get_var_name_length(const char *str)
{
    int i;

    i = 0;
    if (str[i] == '?')
        return (1);
    while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
        i++;
    return (i);
}

static char *get_env_value(const char *var_name)
{
    char *value;

    if (ft_strcmp(var_name, "?") == 0)
        return (ft_itoa(0)); // You'll need to replace 0 with actual exit status
    value = getenv(var_name);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
}

char *expand_env_var(t_parser *parser)
{
    char *var_name;
    char *value;
    int var_len;
    int start;

    start = parser->pos;
    var_len = get_var_name_length(parser->input + start + 1);
    if (var_len == 0)
        return (ft_strdup("$"));
    
    var_name = ft_substr(parser->input, start + 1, var_len);
    value = get_env_value(var_name);
    free(var_name);
    
    parser->pos += var_len + 1;
    return (value);
}

int handle_env_var(t_parser *parser)
{
    char *value;

    if (parser->input[parser->pos] == '$')
    {
        value = expand_env_var(parser);
        if (!value)
            return (0);
        add_token(&parser->tokens, create_token(DOLLAR, value));
        return (1);
    }
    return (0);
} 