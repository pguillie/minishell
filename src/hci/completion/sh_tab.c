#include "shell.h"

static void	sh_tab_token(t_line *line, t_token *token, char **lexeme, int *cat)
{
	size_t	i;

	i = 0;
	while (i < line->cur && token)
	{
		//ft_printf("token: %d `%s' -- our: %d `%s'\n", token->category, token->lexeme, *cat, *lexeme);
		if (ft_strnequ(line->str + i, token->lexeme, ft_strlen(token->lexeme)))
		{
			*lexeme = token->lexeme;
			*cat = token->category;
			if (*cat >= 0)
			{
				*cat = (*cat > 0 ? CMD : FILDES);
				*lexeme = "";
			}
			i += ft_strlen(token->lexeme);
			token = token->next;
		}
		else
		{
			*lexeme = "";
			*cat = token->category;
			i += 1;
		}
	}
}

int			sh_tab(t_line *line, t_token *lex, t_coord **coord, t_tc tc)
{
	char	**array;
	char 	*lexeme;
	int		category;
	int		ret;

	lexeme = "";
	category = CMD;
	if (lex)
		sh_tab_token(line, lex, &lexeme, &category);
	if (!(array = sh_tab_find(lexeme, category)))
		return (0);
	if (array[0] && !array[1])
		ret = sh_tab_comp(line, coord, tc, array[0]);//
	else
		ret = sh_tab_multi(line, coord, tc, array);
	ft_strtabdel(array);
	return (ret);
}
