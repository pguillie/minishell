/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 11:35:32 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/10 11:36:36 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_echo(char *av[])
{
	size_t	i;
	int		nl;

	i = 1;
	nl = 1;
	while (av[i] && ft_strnequ(av[i], "-n", 2))
	{
		nl = 0;
		i++;
	}
	while (av[i])
	{
		ft_putstr(av[i++]);
		if (av[i])
			ft_putchar(' ');
	}
	if (nl)
		ft_putchar('\n');
	return (0);
}
