#include "shell.h"

static int	sh_edit_loop(t_line *line, t_token **lexer, t_tc *tc, char **save)
{
	int		ret;

	ret = LEX_LOOP;
	*save = NULL;
	while (ret & LEX_LOOP)
	{
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		tc->esc = NULL;
		tc->prompt = sh_prompt(!*save ? 1 : 2);
		ret = sh_edit_line(&line, save, lexer, tc);
		if (ret < 0 || ret == EOT)
			break ;
		if (ret & LEX_OK)
			ret = sh_verification(*lexer);
	}
	return (ret);
}

int			sh_edit(t_line *line, char *last, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				ret;

	if (term_raw(&backup, 0, 1))
		return (-1);
	save = NULL;
	ret = sh_edit_loop(line, lexer, tc, &save);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
	{
		ft_error("Unable to restore termios structure", NULL, NULL);
		ret = -1;
	}
	if (ret < 0 || ret & EOT || ret & SYN_ERR)
		sh_token_del(lexer);
	else if (sh_hist_write(save, last))
		ft_error("Unable to write line in history", NULL, NULL);
	save ? ft_strdel(&save) : 0;
	return (g_sig == SIGINT ? 1 : ret);
}
