#include "builtins.h"
#include "utils.h"

static int count_env_vars(char **envp)
{
    int count;

    count = 0;
    while (envp[count])
        count++;
    return (count);
}

static char **create_env_copy(char **envp, int count)
{
    char **sorted_env;
    int i;

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

static void sort_env_array(char **env_array, int count)
{
    char *temp;
    int i;
    int j;

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

static void print_declare_format(char **sorted_env, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        ft_putstr_fd("declare -x ", 1);
        ft_putendl_fd(sorted_env[i], 1);
        free(sorted_env[i]);
        i++;
    }
}

static void print_env_sorted(t_shell_state *state)
{
    char **envp;
    char **sorted_env;
    int count;

    envp = get_env_array_from_state(state);
    if (!envp)
        return;
    count = count_env_vars(envp);
    sorted_env = create_env_copy(envp, count);
    if (!sorted_env)
    {
        free_env_array(envp);
        return;
    }
    sort_env_array(sorted_env, count);
    print_declare_format(sorted_env, count);
    free(sorted_env);
    free(envp);
}

static int validate_export_name(char *name)
{
    int i;

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

static void print_export_error(char *name)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(name, 2);
    ft_putstr_fd("': not a valid identifier\n", 2);
}

static char *extract_key(char *arg, char *eq_pos)
{
    return (ft_substr(arg, 0, eq_pos - arg));
}

static char *extract_value(char *eq_pos)
{
    return (ft_strdup(eq_pos + 1));
}

static int export_with_value(t_shell_state *state, char *arg)
{
    char *eq_pos;
    char *key;
    char *value;

    eq_pos = ft_strchr(arg, '=');
    key = extract_key(arg, eq_pos);
    if (!key)
        return (1);
    if (!validate_export_name(key))
    {
        print_export_error(key);
        free(key);
        return (1);
    }
    value = extract_value(eq_pos);
    if (!value)
    {
        free(key);
        return (1);
    }
    set_env_value_in_state(state, key, value);
    free(key);
    free(value);
    return (0);
}

static int export_without_value(t_shell_state *state, char *arg)
{
    if (!validate_export_name(arg))
    {
        print_export_error(arg);
        return (1);
    }
    set_env_value_in_state(state, arg, "");
    return (0);
}

int ft_export(int argc, char **argv, t_shell_state *state)
{
    int i;
    int exit_status;

    if (argc == 1)
    {
        print_env_sorted(state);
        return (0);
    }
    exit_status = 0;
    i = 1;
    while (i < argc)
    {
        if (ft_strchr(argv[i], '='))
        {
            if (export_with_value(state, argv[i]) != 0)
                exit_status = 1;
        }
        else
        {
            if (export_without_value(state, argv[i]) != 0)
                exit_status = 1;
        }
        i++;
    }
    return (exit_status);
}
