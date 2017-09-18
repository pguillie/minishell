/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:00:10 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/18 20:28:12 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_cd_path(char **curpath, char *env[])
{
	char	**cdpath;
	char	*fpath;
	size_t	i;
	int		ret;

	if (!(cdpath = sh_envvarsplit(sh_getenv("CDPATH", env))))
		return (-1);
	fpath = NULL;
	ret = 0;
	i = 0;
	while (cdpath[i])
	{
		fpath = ft_strcjoin(cdpath[i] ? cdpath[i] : ".", *curpath, '/');
		if (access(fpath, F_OK) == 0)
			break ;
		ft_strdel(&fpath);
		i++;
	}
	ft_strtabdel(cdpath);
	if (fpath)
	{
		*curpath = fpath;
		ret = 1;
	}
	return (ret);
}

static int	sh_cd_opt(char *av[], char *opt)
{
	int		i;
	int		j;

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

static char *sh_cd_logpath(char *path)
{
	size_t  i;
	size_t  j;

	i = 0;
	while (path[i])
	{
		if (ft_strnequ(path + i, "/./", 3) || ft_strequ(path + i, "/."))
			ft_memmove(path + i + 1, path + i + 2, ft_strlen(path + i + 1));
		else if (ft_strnequ(path + i, "//", 2))
			ft_memmove(path + i, path + i + 1, ft_strlen(path + i));
		else if (ft_strnequ(path + i, "/../", 4) || ft_strequ(path + i, "/.."))
		{
			j = i > 0 ? i - 1 : 0;
			while (j && path[j] != '/')
				j--;
			ft_memmove(path + j + 1, path + i + 2, ft_strlen(path + j + 1));
			i = j;
		}
		else if (ft_strequ(path + i, "/") && i)
			path[i] = '\0';
		else
			i++;
	}
	return (path);
}

//ca leaks
int			sh_cd(char *av[], char **env[])
{
	char	*curpath;
	char	cwd[PATH_MAX];
	char	opt;
	int		success;
	int		i;

	opt = 'L';
	if ((i = sh_cd_opt(av, &opt)) < 0)
		return (sh_ill_opt(av[0], opt));
	if (av[i] && av[i + 1])
		return (ft_error(av[0], E_2MNARG, NULL));
	if (!(curpath = av[i] ? av[i] : sh_getenv("HOME", *env)))
		return (ft_error(av[0], "environment variable `HOME' not set", NULL));
	//	printf("dir : %s\n", curpath);//
	if (ft_strequ(curpath, "-"))
		if (!(curpath = sh_getenv("OLDPWD", *env)))
			return (ft_error(av[0], "environment variable `OLDPWD' not set", NULL));
	if (curpath[0] != '/'
			&& !ft_strequ(curpath, ".") && !ft_strequ(curpath, "..")
			&& !ft_strnequ(curpath, "./", 2) && !ft_strnequ(curpath, "../", 3))
	{
		success = sh_cd_path(&curpath, *env);
		if (success < 0)
			return (ft_error(av[0], "Unable to open `CDPATH' environment variable "
						"or current directory", NULL));
		if (success == 0)
			return (ft_error(av[0], curpath, E_NOENT));
	}
	if (opt == 'L')
	{
		if (curpath[0] != '/')
			curpath = ft_strcjoin(sh_getenv("PWD", *env), curpath, '/');
		curpath = sh_cd_logpath(curpath);
	}
	if (chdir(curpath) < 0)
		return (ft_error(av[0], "Unable to change directory.", NULL));
	if (ft_strequ(av[i], "-"))
		ft_putendl(sh_getenv("OLDPWD", *env));
	sh_setenv_nam_val("OLDPWD", sh_getenv("PWD", *env), env);
	if (opt == 'P')
	{
		if (getcwd(cwd, PATH_MAX))
			sh_setenv_nam_val("PWD", cwd, env);
		else
			return (ft_error(av[0], "Unable to set `PWD' environment variable", NULL));
	}
	else
		sh_setenv_nam_val("PWD", curpath, env);
	return (0);
}