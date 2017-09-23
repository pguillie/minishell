#include "shell.h"

static void	handler(int sig)
{
	g_sig = sig;
}

void		sh_init_sig(void)
{
	struct sigaction	act;
	struct sigaction	ign;

	ft_memset(&act, 0, sizeof(act));
	ft_memset(&ign, 0, sizeof(ign));
	act.sa_handler = handler;
	ign.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, 0);
	signal(SIGQUIT, SIG_IGN);
	sigaction(SIGTSTP, &ign, 0);
	signal(SIGCONT, SIG_IGN);
}
