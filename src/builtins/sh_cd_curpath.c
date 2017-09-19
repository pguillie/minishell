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
		if ((fpath = ft_strcjoin(cdpath[i] ? cdpath[i] : ".", *curpath, '/')))
		{
			if (access(fpath, F_OK) == 0)
				break ;
			ft_strdel(&fpath);
		}
		i++;
	}
	ft_strtabdel(cdpath);
	if (fpath && (ret = 1))
		*curpath = fpath;
	return (ret);
}

static char	*sh_cd_logpath(char *path)
{
	size_t	i;
	size_t	j;

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

static int	sh_cd_l(char **curpath, char **env[], int opt, int ret)
{
	char	*tmp;

	if (opt == 'L')
	{
		if ((*curpath)[0] != '/')
		{
			tmp = *curpath;
			*curpath = ft_strcjoin(sh_getenv("PWD", *env), tmp, '/');
			ret ? ft_strdel(&tmp) : 0;
			if (!*curpath)
				return (1);
			ret = 2;
		}
		*curpath = sh_cd_logpath(*curpath);
	}
	return (ret);
}

int			sh_cd_curpath(char *cd, char **curpath, char **env[], char opt)
{
	int		success;
	int		ret;

	ret = 0;
	if ((*curpath)[0] != '/'
			&& !ft_strequ(*curpath, ".") && !ft_strequ(*curpath, "..")
			&& !ft_strnequ(*curpath, "./", 2)
			&& !ft_strnequ(*curpath, "../", 3))
	{
		success = sh_cd_path(curpath, *env);
		if (success < 0)
		{
			return (ft_error(cd, "Unable to open `CDPATH' environment variable "
					"or current directory", NULL));
		}
		if (success == 0)
			return (ft_error(cd, *curpath, E_NOENT));
		ret = 2;
	}
	else if (access(*curpath, F_OK) < 0)
		return (ft_error(cd, *curpath, E_NOENT));
	return (sh_cd_l(curpath, env, opt, ret));
}
