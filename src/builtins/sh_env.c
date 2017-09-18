#include "shell.h"

static int	sh_env_opt(char *av[], char *opt)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "--"))
			return (i + 1);
		j = 1;
		while (av[i][j])
		{
			if (av[i][j] != 'i')
			{
				ft_printf("%s: illegal option -- `%c'\n", av[0], av[i][j]);
				return (-1);
			}
			opt[0] = 'i';
			j++;
		}
		i++;
	}
	return (i);
}

int		sh_env(char *av[], char *env[])
{
	char	**env_mod;
	char	opt[2];
	int		i;
	int		ret;


	ft_memset(opt, 0, sizeof(char) * 2);
	env_mod = NULL;
	ret = 0;
	i = sh_env_opt(av, opt);
	if (i < 0)
		return (1);
	if (opt[0] != 'i' && !(env_mod = sh_envdup(env)))
		return (ft_error(av[0], "Unable to duplicate environment", NULL));
	while (ft_strchr(av[i], '='))
		sh_setenv_line(av[i++], &env_mod);
	if (av[i])
	{
		if (!sh_builtin(av + i, &env_mod, &ret))
			ret = sh_execution(av + i, env_mod);
	}
	else
		sh_dispenv(env_mod);
	sh_envdel(&env_mod);
	return (ret);
}
