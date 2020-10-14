/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 13:57:54 by laballea          #+#    #+#             */
/*   Updated: 2020/10/14 08:12:56 by laballea         ###   ########.fr       */
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
		write(1, "Quit (core dumped)\n", 19);
}
