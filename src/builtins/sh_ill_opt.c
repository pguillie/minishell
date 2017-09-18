/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_ill_opt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/14 13:57:49 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/14 14:09:48 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ill_opt(char *fct, char opt)
{
	ft_putstr_fd(fct, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("Illegal option -- ", 2);
	ft_putchar_fd('`', 2);
	ft_putchar_fd(opt, 2);
	ft_putchar_fd('\'', 2);
	ft_putchar_fd('\n', 2);
	return (1);
}
