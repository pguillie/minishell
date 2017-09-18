#include "shell.h"

int		sh_putesc(t_line **line, t_coord **coord, t_tc *tc)
{
	t_line	*target;
	int		ret;

	ret = 0;
/*	int i = 1;
	while (tc->esc[i])
	{
		ft_printf("%d -- `%c'\n", i, tc->esc[i]);
		i++;
	}
*/	if (sh_move_able(tc->esc, *line, *coord))
		(*line)->cur = sh_move_cur((*line)->cur, (*line)->pos, *coord, *tc);
	else if ((target = sh_hist_able(tc->esc, *line)))
		ret = sh_hist(line, coord, *tc, target);
	else if (sh_del_able(tc->esc, *line))
		ret = sh_del_r(*line, coord, *tc);
	else if (tc->esc[1] == '\n')
		ret = sh_ins(*line, coord, *tc, '\n');
	//...
	ft_strdel(&(tc->esc));
	return (ret);
}
