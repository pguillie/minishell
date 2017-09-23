#include "shell.h"

static int	sh_cd_opt(char *av[], char *opt)
{
	int		i;
	int		j;

	*opt = 'L';
	if (!av[1])
		return (1);
	i = 1;
	while (av[i] && av[i][0] == '-')
	{
		if (ft_strequ(av[i], "-"))
			return (i);
		if (ft_strequ(av[i], "--"))
			return (i + 1);
		j = 1;
		while (av[i][j])
		{
			*opt = av[i][j];
			if (av[i][j] != 'L' && av[i][j] != 'P')
				return (-1);
			j++;
		}
		i++;
	}
	return (i);
}

static int	sh_cd_env(char *curpath, char **env[], char opt)
{
	char	tmp[PATH_SIZE];
	char	cwd[PATH_SIZE];
	int		ret;

	if (ft_strequ(curpath, "-"))
		ft_putendl(curpath);
	ft_strncpy(tmp, curpath, PATH_SIZE);
	ret = sh_setenv_nam_val("OLDPWD", sh_getenv("PWD", *env), env);
	if (opt == 'P')
	{
		if (getcwd(cwd, PATH_SIZE))
			ret = sh_setenv_nam_val("PWD", cwd, env);
		else
			return (ft_error("cd", E_SETENV("PWD"), NULL));
	}
	else
		ret = sh_setenv_nam_val("PWD", tmp, env);
	return (ret);
}

static int	sh_cd_dir(char *curpath, int free)
{
	struct stat	buf;

	if (stat(curpath, &buf) < 0)
	{
		free ? ft_strdel(&curpath) : 0;
		return (-1);
	}
	if (!S_ISDIR(buf.st_mode))
	{
		ft_error("cd", curpath, "Not a directory");
		free ? ft_strdel(&curpath) : 0;
		return (1);
	}
	return (0);
}

static int	sh_cd_end(char *curpath, char **env[], char opt, int free)
{
	if (chdir(curpath) < 0)
	{
		free ? ft_strdel(&curpath) : 0;
		return (ft_error("cd", "Unable to change directory", NULL));
	}
	if (sh_cd_env(curpath, env, opt))
	{
		free ? ft_strdel(&curpath) : 0;
		return (ft_error("cd", "Some environment variables could"
					" not be set correctly", NULL));
	}
	if (free)
		ft_strdel(&curpath);
	return (0);
}

int			sh_cd(char *av[], char **env[])
{
	char	*curpath;
	char	opt;
	int		i;
	int		free;

	if ((i = sh_cd_opt(av, &opt)) < 0)
		return (sh_ill_opt(av[0], opt));
	if (av[i] && av[i + 1])
		return (ft_error(av[0], E_2MNARG, NULL));
	if (!(curpath = av[i] ? av[i] : sh_getenv("HOME", *env)))
		return (ft_error(av[0], "environment variable `HOME' not set", NULL));
	if (ft_strequ(av[i], "-") && !(curpath = sh_getenv("OLDPWD", *env)))
		return (ft_error(av[0], "environment variable `OLDPWD' not set", NULL));
	if ((free = sh_cd_curpath(av[0], &curpath, env, opt)) == 1)
		return (-1);
	if (sh_cd_dir(curpath, free))
		return (1);
	return (sh_cd_end(curpath, env, opt, free));
}
