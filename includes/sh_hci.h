#ifndef SH_HCI_H
# define SH_HCI_H

/*
**	HUMAN-COMPUTER INTERACTION
*/

int		sh_hci(t_tc *termcaps, t_token **lexer, int ret);
int		sh_edit(t_line *line, char *last, t_token **lexer, t_tc *termcaps);

/*
**	X-ABLE
*/

int		sh_move_able(char *esc, t_line *line, t_coord *coord);
int		sh_del_able(char *esc, t_line *line);
t_line	*sh_hist_able(char *esc, t_line *line);

/*
**	COMPLETION
*/

int		sh_tab(t_line *line, t_token *lexer, t_coord **coord, t_tc tc);
char	**sh_tab_find(char *array[], char *dir, int cat);
int		sh_tab_comp(t_line *line, t_coord **coord, t_tc tc, char *buf);
int		sh_tab_multi(t_line *line, t_coord **coord, t_tc tc, char *array[]);

/*
**	CONVERTIONS
*/

char	sh_conv(char *str);
char	sh_conv_oct(char *str);
char	sh_conv_hex(char *str);

/*
**	CUR_MOTION
*/

int		sh_cur_motion(long input, t_line *line, size_t *pos, t_coord *coord);
size_t	sh_move_cur(size_t origin, size_t dest, t_coord *coord, t_tc tc);
size_t	sh_move_line_u(t_line *line, t_coord *coord);
size_t	sh_move_line_d(t_line *line, t_coord *coord);
size_t	sh_move_word_r(t_line *line);
size_t	sh_move_word_l(t_line *line);
t_coord	*sh_create_coord(t_line *line, size_t prompt);

/*
**	EDITION
*/

int		sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc);
int		sh_esc(t_line **line, t_coord **coord, t_tc *tc);
int		sh_putesc(t_line **line, t_coord **coord, t_tc *tc);
void	sh_clear(t_line *line, t_coord *coord, t_tc tc);
void	sh_display(t_line *line, t_coord *coord, t_tc tc);
int		sh_del_l(t_line *line, t_coord **coord, t_tc tc);
int		sh_del_r(t_line *line, t_coord **coord, t_tc tc);
int		sh_ctrl_d(t_line *line, t_coord **coord, t_tc tc, char *save);
int		sh_hist(t_line **line, t_coord **coord, t_tc tc, t_line *target);
int		sh_ins(t_line *line, t_coord **coord, t_tc tc, char c);
int		termput(int c);

/*
**	HISTORY
*/

t_line	*sh_hist_read(void);
t_line	*sh_hline_new(char *str, t_line *prev);
int		sh_hist_write(char *line, char *last);
void	sh_hist_del(t_line **hist);

/*
**	LEXER
*/

t_token	*sh_token_new(char *lexeme, size_t *i, int *status);
int		sh_lexer(char *str, t_token **begin);
int		sh_lex_word(char *str);
int		sh_metachar(char c);
int		sh_ctrl_op(char *str);
int		sh_rdir_op(char *str);
int		sh_token_del(t_token **begin);
int		sh_category(char *str, size_t *i, int *status);
int		sh_verification(t_token *lexer);

/*
**	PROMPT
*/

int		sh_prompt(int mode);
int		sh_print_prompt(char *ps);
int		sh_prompt_conv(char *ps, char buff[], int *b, int *len);

int		sh_prt_strftime(char buff[], int *b, char *format, struct tm *tm);
void	sh_prt_chr(char buff[], int *b, char c, int *len);
int		sh_prt_date(char buff[], int *b, char *ps, int *len);
int		sh_prt_esc(char buff[], int *b, char *ps);
int		sh_prt_host(char buff[], int *b, char h);
int		sh_prt_shell(char buff[], int *b);
int		sh_prt_term(char buff[], int *b);
int		sh_prt_time(char buff[], int *b, char t);
int		sh_prt_user(char buff[], int *b);
int		sh_prt_vers(char buff[], int *b, char v);
int		sh_prt_wdir(char buff[], int *b, char w);
int		sh_prt_uid(char buff[], int *b);

#endif
