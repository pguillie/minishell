#include "shell.h"

static int	sh_pipe_left(t_tree *root, int pipe_out)
{
	int		stdout;
	int		stderr;
	int		ret;

	stdout = dup(1);
	stderr = dup(2);
	dup2(pipe_out, 1);
	if (ft_strequ(root->op, "|&"))
		dup2(pipe_out, 2);
	ret = sh_tree_browse(root->left);
	close(pipe_out);
	dup2(stdout, 1);
	dup2(stderr, 2);
	exit(ret);
}

static int	sh_pipe_right(t_tree *root, int pipe_in)
{
	int		stdin;
	int		ret;

	stdin = dup(0);
	dup2(pipe_in, 0);
	ret = sh_tree_browse(root->right);
	close(pipe_in);
	dup2(stdin, 0);
	return (ret);
}

static int	sh_pipe(t_tree *root)
{
	pid_t	child;
	int		fildes[2];
	int		ret;

	if (pipe(fildes) < 0)
		return (-1);
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		close(fildes[0]);
		exit(sh_pipe_left(root, fildes[1]));
	}
	else
	{
		waitpid(child, &ret, 0);
		close(fildes[1]);
		ret = sh_pipe_right(root, fildes[0]);
	}
	return (ret);
}

int			sh_tree_browse(t_tree *root)
{
	extern char	**environ;
	int			ret;

	if (!root)
		return (0);
	ret = -1;
	if (root->cmd)
	{
		if (!sh_builtin(root->cmd->av, &environ, &ret))
			ret = sh_execution(root->cmd->av, environ);
	}
	else if (root->op)
	{
		if (ft_strequ(root->op, "|") || ft_strequ(root->op, "|&"))
			ret = sh_pipe(root);
		else
		{
			ret = sh_tree_browse(root->left);
			if (!(ft_strequ(root->op, "&&") && ret)
					&& !(ft_strequ(root->op, "||") && !ret) && root->right)
				ret = sh_tree_browse(root->right);
		}
	}
	return (ret);
}
