#include "shell.h"

int		sh_prt_shell(char buff[], int *b)
{
	char	*shell;
	int		i;

	shell = SHELL;
	i = 0;
	while (shell[i])
	{
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = shell[i++];
	}
	return (i);
}
