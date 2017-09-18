/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 11:54:08 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/10 16:55:41 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_unsetenv_remove(char **env[], size_t pos, size_t size)
{
	char	**new;
	size_t	i;

	if (!(new = (char**)ft_memalloc(sizeof(char*) * (size))))
		return (1);
	i = size - 1;
	while (size--)
	{
		if (size != pos)
			new[--i] = (*env)[size];
	}
	ft_memdel((void**)env);
	*env = new;
	return (0);
}

int			sh_unsetenv_name(char *name, char **env[])
{
	size_t	i;
	int		pos;

	i = 0;
	pos = -1;
	while ((*env)[i])
	{
		if (ft_strnequ((*env)[i], name, ft_strlen(name))
				&& ft_strcmp((*env)[i], name) == '=')
			pos = i;
		i++;
	}
	if (pos >= 0)
		return (sh_unsetenv_remove(env, pos, i));
	return (0);
}

int			sh_unsetenv(char *av[], char **env[])
{
	size_t	i;

	i = 1;
	while (av[i])
	{
		if (sh_unsetenv_name(av[i], env))
			return (ft_error(av[i], "Unable to remove variable from environment", NULL));
		i++;
	}
	if (i == 1)
		return (ft_error(av[0], E_2FWARG, NULL));
	return (0);
}
