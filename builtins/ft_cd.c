#include "builtins.h"
#include "utils.h"

static char *get_env_var(char *var, char **envp)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen(var);
    while (envp[i])
    {
        if (ft_strncmp(envp[i], var, len) == 0 && envp[i][len] == '=')
            return (envp[i] + len + 1);
        i++;
    }
    return (NULL);
}

int ft_cd(int argc, char **argv, char ***envp)
{
    char *path;
    char cwd[1024];
    char *old_pwd;

    if (argc > 2)
    {
        ft_putstr_fd("cd: too many arguments\n", 2);
        return (1);
    }
    old_pwd = get_env_var("PWD", *envp);
    if (argc == 1 || ft_strcmp(argv[1], "~") == 0)
        path = get_env_var("HOME", *envp);
    else if (ft_strcmp(argv[1], "-") == 0)
    {
        path = get_env_var("OLDPWD", *envp);
        if (path)
            ft_putendl_fd(path, 1);
    }
    else
        path = argv[1];
    if (!path)
    {
        ft_putstr_fd("cd: path not set\n", 2);
        return (1);
    }
    if (chdir(path) != 0)
    {
        perror("cd");
        return (1);
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        set_env_var("OLDPWD", old_pwd, envp);
        set_env_var("PWD", cwd, envp);
    }
    return (0);
} 