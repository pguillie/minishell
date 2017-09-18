#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_builtin(char *av[], char **env[], int *ret);
int		sh_cd(char *av[], char **env[]);
int		sh_echo(char *av[]);
int		sh_env(char *av[], char *env[]);
int		sh_exit(char *av[], int ret);
int		sh_setenv(char *av[], char **env[]);
int		sh_setenv_line(char *line, char **env[]);
int		sh_setenv_nam_val(char *name, char *value, char **env[]);
int		sh_unsetenv(char *av[], char **env[]);
int		sh_unsetenv_name(char *name, char **env[]);
int		sh_ill_opt(char *fct, char opt);

#endif
