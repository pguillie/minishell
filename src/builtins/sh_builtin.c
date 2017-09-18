/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 11:26:07 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/18 15:09:54 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_builtin(char *av[], char **env[], int *ret)
{
	if (ft_strequ(av[0], "echo"))
		*ret = sh_echo(av);
	else if (ft_strequ(av[0], "cd"))
		*ret = sh_cd(av, env);
	else if (ft_strequ(av[0], "setenv"))
		*ret = sh_setenv(av, env);
	else if (ft_strequ(av[0], "unsetenv"))
		*ret = sh_unsetenv(av, env);
	else if (ft_strequ(av[0], "env"))
		*ret = sh_env(av, *env);
	else if (ft_strequ(av[0], "exit"))
		*ret = sh_exit(av, *ret);
	else
		return (0);
	return (1);
}
