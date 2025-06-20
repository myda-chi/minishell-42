#include "libft.h"

char **copy_envp(char **envp)
{
    int count;
    char **new_envp;
    int i;

    count = 0;
    while (envp[count])
        count++;
    new_envp = malloc(sizeof(char *) * (count + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    while (i < count)
    {
        new_envp[i] = ft_strdup(envp[i]);
        if (!new_envp[i])
        {
            // free already allocated strings
            return (NULL);
        }
        i++;
    }
    new_envp[i] = NULL;
    return (new_envp);
}

void set_env_var(char *var, char *value, char ***envp)
{
    int i;
    int len;
    char *new_var;

    i = 0;
    len = ft_strlen(var);
    new_var = ft_strjoin(var, "=");
    new_var = ft_strjoin(new_var, value);
    while ((*envp)[i])
    {
        if (ft_strncmp((*envp)[i], var, len) == 0 && (*envp)[i][len] == '=')
        {
            free((*envp)[i]);
            (*envp)[i] = new_var;
            return;
        }
        i++;
    }
    // if not found, add it by reallocating envp
    char **new_envp = malloc(sizeof(char *) * (i + 2));
    if (!new_envp)
    {
        free(new_var);
        return;
    }
    i = 0;
    while ((*envp)[i])
    {
        new_envp[i] = (*envp)[i];
        i++;
    }
    new_envp[i] = new_var;
    new_envp[i+1] = NULL;
    free(*envp);
    *envp = new_envp;
} 