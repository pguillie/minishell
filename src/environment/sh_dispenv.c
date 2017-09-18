#include "shell.h"

void	sh_dispenv(char *env[])
{
	size_t	i;

	if (env)
	{
		i = 0;
		while (env[i])
			ft_putendl(env[i++]);
	}
}
