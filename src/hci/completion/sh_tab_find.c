#include "shell.h"

static void	sh_tab_append(char **array[], char *occ, char c)
{
	char	**new;
	size_t	i;

	i = 0;
	if (*array)
		while ((*array)[i])
			i += 1;
	if ((new = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
	{
		if ((new[i] = ft_strnew(ft_strlen(occ) + 1)))
		{
			ft_strcpy(new[i], occ);
			ft_strncat(new[i], &c, 1);
			while (i--)
				new[i] = (*array)[i];
			free(*array);
			*array = new;
		}
		else
			free(new);
	}
}

static void	sh_tab_norminette(char path[], char *dir, char *fil)
{
	ft_strncpy(path, dir, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, fil, PATH_MAX);
}

static void	sh_tab_open(char **array[], char *dir, int cat)
{
	DIR				*dirp;
	struct dirent	*de;
	struct stat		buf;
	char			path[PATH_MAX];
	size_t			len;

	if ((dirp = opendir(dir)))
	{
		len = ft_strlen(*array[0]);
		while ((de = readdir(dirp)))
		{
			if (ft_strnequ(*array[0], de->d_name, len)
					&& !ft_strequ(de->d_name, "..")
					&& !ft_strequ(de->d_name, "."))
			{
				sh_tab_norminette(path, dir, de->d_name);
				if (stat(path, &buf) == 0
						&& (cat != CMD || S_ISDIR(buf.st_mode)
							|| S_IXUSR & buf.st_mode))
					sh_tab_append(array, de->d_name, S_ISDIR(buf.st_mode)
							? '/' : 0);
			}
		}
		closedir(dirp);
	}
}

char		**sh_tab_find(char *array[], char *dir, int category)
{
	char	**path;
	size_t	i;

	if (category == CMD && ft_strequ(dir, "."))
	{
		i = 0;
		path = NULL;
		if (!(path = sh_envvarsplit(getenv("PATH"))))
			return (NULL);
		while (path[i])
		{
			sh_tab_open(&array, path[i], category);
			i += 1;
		}
		ft_strtabdel(path);
	}
	else
		sh_tab_open(&array, dir, category);
	return (array);
}
