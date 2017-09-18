/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/10 17:42:22 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/10 18:05:59 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_exit(char *av[], int ret)
{
	if (av[1])
	{
		if (av[2])
			return (ft_error(av[0], E_2MNARG, NULL));
		exit(ft_atoi(av[1]));
	}
	exit(WEXITSTATUS(ret));
}
