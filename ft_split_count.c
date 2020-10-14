/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 09:01:27 by laballea          #+#    #+#             */
/*   Updated: 2020/10/08 09:11:43 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			help_count_size2(char const **s, char c, int *n, int *i)
{
	if (*(*s) != c && !(*n))
	{
		(*n)++;
		(*i)++;
	}
	if (*(*s) == c)
		(*n) = 0;
	if (*(*s))
		(*s)++;
}

int				count_size_mini(char const *s, char c)
{
	int		i;
	int		j;
	int		n;
	char	mem;

	mem = '\0';
	j = 0;
	i = 0;
	n = 0;
	while (s[j])
	{
		if (s[j] == '\'' || s[j] == '"')
		{
			mem = s[j];
			while (s[j] != mem && s[j])
				j++;
		}
		help_count_size2(&s, c, &n, &i);
	}
	return (i);
}
