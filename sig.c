/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:57:54 by laballea          #+#    #+#             */
/*   Updated: 2020/10/30 12:00:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint(int i)
{
	(void)i;
	if (!g_gpid)
	{
		g_stt = 130;
		write(1, "\nminishell>", 12);
	}
	else
		g_stt = 130;
}

void	signothing(int i)
{
	(void)i;
	if (!g_gpid)
		return ;
	else
	{
		write(1, "Quit (core dumped)\n", 19);
		g_stt = 131;
	}
}

void	chev_r_line(char **arg, int *i, t_var *fd, int n)
{
	char *tmp;

	tmp = del_quote(arg[(*i) + 2]);
	fd->fd_out[n] = open(tmp, O_RDWR |
	O_APPEND | O_CREAT, 0660);
	(*i) += 2;
	free(tmp);
}
