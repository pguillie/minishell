#ifndef SHELL_H
# define SHELL_H

/*
**	EXTERN LIB
*/

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
# include <pwd.h>
# include <dirent.h>
# include <termcap.h>
# include <time.h>

/*
**	DEFINE
*/

# define SHELL "minishell"
# define VERSION "1.0"
# define PATCH "0"

# define HIST_FILE ".minishell_history"
# define ERROR_MAX 5
# define PATH_SIZE 2048
# define PRT_SIZE 256
# define PROMPT_DIRTRIM 3
# define PS1 "\\s-\\v\\$ "
# define PS2 "> "
# define PS3 "#? "
# define PS4 "+ "

# define EOT 8
# define EOL 4
# define LEXER 2
# define DISP 1
# define DISP_FULL 17

# define SYN_ERR 4
# define LEX_LOOP 2
# define LEX_OK 1

# define UP 1
# define DOWN 2
# define RIGHT 4
# define LEFT 8
# define END 32
# define HOME 128
# define CTL 64

# define CASE(x) (x | 32)

/*
**	RESSOURCES
*/

# include "../libft/includes/libft.h"
# include "sh_category.h"
# include "sh_struct.h"

/*
**	PROTOTYPES
*/

# include "sh_builtins.h"
# include "sh_environment.h"
# include "sh_execution.h"
# include "sh_expansion.h"
# include "sh_hci.h"
# include "sh_initialization.h"
# include "sh_parser.h"
# include "sh_signal.h"

////////////////
void displex(t_token *lexer);
void disphist(t_line *line);
void dispcoord(t_coord *c, t_line *l);
void disptree(t_tree *root);
////////////////

#endif
