#include "shell.h"

int		sh_prompt(int mode)
{
	char	*ps;

	ps = NULL;
	if (mode == 1)
		ps = PS1;
	else if (mode == 2)
		ps = PS2;
	else if (mode == 3)
		ps = PS3;
	else if (mode == 4)
		ps = PS4;
	return (sh_print_prompt(ps));
}
