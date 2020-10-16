/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 09:54:59 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 20:19:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		rt_read(int ret, char **buf)
{
	free(*buf);
	return (ret);
}

int		g_save_ret(char *save)
{
	g_save = save;
	return (1);
}

void	replace_pipe(char **flag)
{
	int i;

	i = 0;
	while ((*flag)[i])
	{
		if ((*flag)[i] == 11)
			(*flag)[i] = '|';
		i++;
	}
}
