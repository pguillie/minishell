#include "shell.h"

void	sh_init_loop(t_token **lexer, t_tree **root)
{
	extern char	**environ;
	char		cwd[1024];
	char		*pwd;

	//a tester, secu, etc
	g_sig = 0;
	if (!(pwd = getenv("PWD")))
		sh_setenv_nam_val("PWD", getcwd(cwd, 1024), &environ);//
	*lexer = NULL;
	*root = NULL;
}
