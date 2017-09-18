#include "shell.h"

int		sh_ins(t_line *line, t_coord **coord, t_tc tc, char c)
{
	if (line->used + 1 == line->capacity)
	{
		line->capacity += BUFF_SIZE;
		if (!(line->str = (char*)ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + 1, line->str + line->cur,
			ft_strlen(line->str + line->cur) + 1);
	line->str[line->cur] = c;
	line->used += 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	line->pos = line->cur + 1;
	return (LEXER | DISP);
}
