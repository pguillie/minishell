/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 15:10:45 by pguillie          #+#    #+#             */
/*   Updated: 2016/12/09 14:44:00 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(int n)
{
	int		len;
	double	pow;
	long	l;

	len = 0;
	pow = 1;
	if (n < 0)
		len++;
	l = (long)n;
	while (ABS(l) >= (pow *= 10))
		len++;
	return (len + 1);
}
