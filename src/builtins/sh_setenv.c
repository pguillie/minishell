#include "shell.h"

static int	sh_setenv_array(char *var, char **env[])
{
	char	**new;
	size_t	i;
	size_t	len;

	i = 0;
	while (*env && (*env)[i])
	{
		len = 0;
		while ((*env)[i][len] != '=')
			len++;
		if (ft_strnequ((*env)[i], var, len + 1))
		{
			ft_strdel(&(*env)[i]);
			(*env)[i] = var;
			return (0);
		}
		i++;
	}
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
		return (-1);
	new[i] = var;
	while (i--)
		new[i] = (*env)[i];
	ft_memdel((void**)env);
	*env = new;
	return (0);
}

int		sh_setenv_line(char *line, char **env[])
{
	char	*var;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '=')
	{
		if ((line[i] < 'A' || line[i] > 'Z')
			&& (line[i] < '0' || line[i] > '9') && line[i] != '_')
		{
			ft_error(line, "Environment variables name may contain "
					"uppercase letters and underscore `_' only", NULL);
			return (0);
		}
		i++;
	}
	if (!(var = ft_strdup(line)))
		return (ft_error(line, "Unable to create environment variable", NULL));
	return (sh_setenv_array(var, env));
}

int		sh_setenv_nam_val(char *name, char *value, char **env[])
{
	char	*var;
	size_t	i;

	i = 0;
	while (name[i])
	{
		if ((name[i] < 'A' || name[i] > 'Z')
			&& (name[i] < '0' || name[i] > '9') && name[i] != '_')
		{
			ft_error(name, "Environment variables name may contain "
					"uppercase letters and underscore `_' only", NULL);
			return (0);
		}
		i++;
	}
	if (!(var = ft_strcjoin(name, value ? value : "", '=')))
		return (ft_error(name, "Unable to create environment variable", NULL));
	return (sh_setenv_array(var, env));
}

int		sh_setenv(char *av[], char **env[])
{
	size_t	i;
	int		ret;

	i = 1;
	while (av[i])
	{
		if (ft_strchr(av[i], '='))
			ret = sh_setenv_line(av[i], env);
		else
			ret = sh_setenv_nam_val(av[i], av[i + 1], env);
		if (ret)
			return (ft_error(av[i], "Unable to set variable", NULL));
		i += ft_strchr(av[i], '=') || !av[i + 1] ? 1 : 2;
	}
	return (ret);
}
