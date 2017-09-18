#include "shell.h"

void	sh_envdel(char **env[])
{
	size_t	i;

	if (*env)
	{
		i = 0;
		while ((*env)[i])
			ft_strdel(&(*env)[i++]);
		ft_memdel((void**)env);
	}
}
