/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 13:55:39 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/21 19:10:16 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int			main(void)
{
	t_tc	termcaps;
	t_token	*lexer;
	t_tree	*root;
	int		remaining_error;
	int		ret;

	if (sh_init(&termcaps))
		return (1);
	remaining_error = ERROR_MAX;
	ret = 0;
	while (remaining_error)
	{
		g_sig = 0;
		lexer = NULL;
		root = NULL;
		if (sh_hci(&termcaps, &lexer, ret))
			remaining_error -= 1;
		else if (sh_parser(lexer, &root) < 0)
			remaining_error -= 1;
		else if ((ret = sh_tree_browse(root)) < 0)
			remaining_error -= 1;
		lexer ? sh_token_del(&lexer) : 0;
		root ? sh_tree_del(&root) : 0;
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n");
	return (1);
}
