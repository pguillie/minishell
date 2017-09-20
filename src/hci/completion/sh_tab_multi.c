#include "shell.h"

int		sh_tab_multi(t_line *line, t_coord **coord, t_tc tc, char *array[])
{
	char	occ[PATH_MAX];
	size_t	i;
	size_t	j;
	int		ret;

	ft_strncpy(occ, array[0], PATH_MAX);
	i = 1;
	while (array[i] && occ[0])
	{
		j = 0;
		while (j < PATH_MAX && occ[j] == array[i][j])
			j++;
		ft_strclr(occ + j);
		i += 1;
	}
	if (occ[0])
		ret = sh_tab_comp(line, coord, tc, occ);//secur + "ret = LEXER | DISP"
	else
	{
		ft_printf("\n== tabulation ==\n");
		ft_strtab_disp(array);
		ret = DISP_FULL;
	}
	return (ret);
}
