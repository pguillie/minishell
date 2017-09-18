#ifndef SH_ENVIRONMENT_H
# define SH_ENVIRONMENT_H

char	**sh_envdup(char *env[]);
void	sh_envdel(char **env[]);
char	**sh_envvarsplit(char *value);
char	*sh_getenv(char *name, char *env[]);
void	sh_dispenv(char *env[]);

#endif
