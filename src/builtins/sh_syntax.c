/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 16:57:25 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/11 12:39:49 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_syntax(char **av, char **env[])
{
	int		ret;

	ret = 0;
	if (!av[1])
	{
		if (ft_strequ(getenv("SYNTAX_HIGHLIGHTING"), "true"))
			ret = sh_setenv_line("SYNTAX_HIGHLIGHTING=false", env);
		else
			ret = sh_setenv_line("SYNTAX_HIGHLIGHTING=true", env);
	}
	else if (av[2])
		return (ft_error("syntax", E_2MNARG, NULL));
	else
	{
		if (ft_strequ(ft_strlower(av[1]), "on"))
			ret = sh_setenv_line("SYNTAX_HIGHLIGHTING=true", env);
		else if (ft_strequ(ft_strlower(av[1]), "off"))
			ret = sh_setenv_line("SYNTAX_HIGHLIGHTING=false", env);
		else
			return (ft_error("usage", "syntax [on|off]", NULL));
	}
	return (ret);
}
