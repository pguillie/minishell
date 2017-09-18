#include "shell.h"

static int	sh_cat_sep(char *str)
{
	if (ft_strnequ(str, "||", 2) || ft_strnequ(str, "&&", 2))
		return (ANDOR);
	if (ft_strnequ(str, ";", 1) || ft_strnequ(str, "&", 1))
		return (ESPERCOLON);
	if (ft_strnequ(str, "|", 1))
		return (PIPE);
	if (ft_strnequ(str, "\n", 1))
		return (NEWLINE);
	return (0);
}

int			sh_category(char *str, size_t *i, int *status)
{
	int			sep;

	if (sh_rdir_op(str + i[0]))
		return (REDIRECTION);
	if ((sep = sh_cat_sep(str + i[0])))
	{
		status[0] = CMD;
		return (sep);
	}
	if ((i[1] == 1 && str[i[0]] >= '0' && str[i[0]] <= '9'
			&& sh_rdir_op(str + i[0] + i[1]))
			|| (str[i[0]] != '-' && status[1]))
		return (FILDES);
	if (status[0] == CMD)
		return (status[0]--);
	if (status[0] == OPT)
	{
		if (ft_strnequ(str + i[0], "--", i[1] > 2 ? i[1] : 2))
			return (status[0]--);
		if (str[i[0]] == '-')
			return (status[0]);
		else
			status[0] = ARG;
	}
	return (status[0]);
}
