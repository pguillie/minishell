/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 17:42:22 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/21 19:07:05 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_exit(char *av[], int ret)
{
	if (av && av[1])
	{
		if (av[2])
			return (ft_error(av[0], E_2MNARG, NULL));
		ret = ft_atoi(av[1]);
	}
	ft_putendl("exit");
	exit(ret);
}
