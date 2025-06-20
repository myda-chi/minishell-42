#ifndef UTILS_H
# define UTILS_H

char **copy_envp(char **envp);
void set_env_var(char *var, char *value, char ***envp);

#endif 