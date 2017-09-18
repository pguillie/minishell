#include "shell.h"

int		sh_init_env(void)
{
	extern char	**environ;
	char		**dup;
	char		*shlvl;
	int			ret;

	if (!(dup = sh_envdup(environ)))
		return (-1);
	ret = 1;
	shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	if (!shlvl || sh_setenv_nam_val("SHLVL", shlvl, &dup))
	{
		sh_envdel(&dup);
		shlvl ? ft_strdel(&shlvl) : 0;
		return (-1);
	}
	ft_strdel(&shlvl);
	environ = dup;
	return (ret);
}
