/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_split_help.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 08:29:33 by laballea          #+#    #+#             */
/*   Updated: 2020/09/09 08:32:51 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			*freebuffs(char **buff)
{
	char **tmp;

	tmp = buff;
	while (*tmp)
		free(tmp++);
	free(buff);
	return (0);
}

void			need_line(char *keep, char **s, char ***k)
{
	if (ft_check_in(keep, *(*s)))
	{
		*(*k) = ft_calloc_bis(1, 2 * sizeof(char));
		ft_memcpy(*(*k), *s, 1);
		(*k)++;
	}
}
