#include "shell.h"

static void	sh_tab_append(char **array[], char *occ)
{
	char	**new;
	size_t	i;

	//ft_printf(" ** TRY APP: %s **\n", occ);
	i = 0;
	if (*array)
		while ((*array)[i])
			i += 1;
	if ((new = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
	{
		if ((new[i] = ft_strdup(occ)))
		{
			while (i--)
				new[i] = (*array)[i];
			free(*array);
			*array = new;
			//ft_printf(" ** APPENED ! **\n");
		}
		else
			free(new);
	}
}

static void	sh_tab_open(char **array[], char *dir, char *pattern, int cat)
{
	DIR				*dirp;
	struct dirent	*de;
	struct stat		buf;
	char			path[PATH_MAX];
	size_t			len;

	if ((dirp = opendir(dir)))
	{
		//ft_printf("\t== OPEN %s ==\n", dir);
		len = ft_strlen(pattern);
		while ((de = readdir(dirp)))
		{
			//ft_printf("READ: %s\n", de->d_name);
			if (ft_strnequ(pattern, de->d_name, len)
					&& !ft_strequ(de->d_name, "..")
					&& !ft_strequ(de->d_name, "."))
			{
				ft_strncpy(path, dir, PATH_MAX);
				ft_strlcat(path, "/", PATH_MAX);
				ft_strlcat(path, de->d_name, PATH_MAX);
				//ft_printf("$   EQU : %s %%%d%%\n", path, cat);
				if (stat(path, &buf) == 0
						&& (cat != CMD || S_ISDIR(buf.st_mode)
							|| S_IXUSR & buf.st_mode))
					sh_tab_append(array, de->d_name + len);
			}
		}
		closedir(dirp);
	}
}

static char	*sh_tab_split(char *lexeme, char *dir)
{
	size_t	i;

	if (dir)
		ft_bzero(dir, PATH_MAX);
	i = 0;
	while (lexeme[i])
	{
		if (lexeme[i] == '/')
		{
			if (dir)
				ft_strncat(dir, lexeme, i + 1);
			lexeme += i + 1;
			i = 0;
		}
		else
			i += 1;
	}
	if (dir)
		!dir[0] ? dir[0] = '.' : 0;
	return (lexeme);
}

char		**sh_tab_find(char *lexeme, int category)
{
	char	**array;
	char	**path;
	char	dir[PATH_MAX];
	size_t	i;

	array = NULL;
	i = 0;
	path = NULL;
	//ft_printf("__FIND: %d <%s>\n", category, lexeme);//
	if (category == CMD && !ft_strchr(lexeme, '/'))
	{
		if (!(path = sh_envvarsplit(getenv("PATH"))))
			return (NULL);
		while (path[i + 1])
		{
			sh_tab_open(&array, path[i], lexeme, category);
			i += 1;
		}
	}
	else
	{
		i = 0;
		lexeme = sh_tab_split(lexeme, dir);
		//ft_printf("path: `%s' / `%s'\n", dir, lexeme);//
		sh_tab_open(&array, dir, lexeme, category);
	}
	return (array);
}
