/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:12:03 by laballea          #+#    #+#             */
/*   Updated: 2020/10/20 11:09:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_size(const char *s, char *set, char *keep)
{
	int		nb;
	char	*ptr;

	nb = 0;
	ptr = (char*)s;
	while (*ptr)
	{
		while (*ptr && ft_check_in(set, *ptr))
		{
			if (ft_check_in(keep, *ptr))
				nb++;
			ptr++;
		}
		if (*ptr != '\0')
			nb++;
		while (*ptr && !ft_check_in(set, *ptr))
			ptr++;
	}
	return (nb);
}

void			split_help(char **s, char *set, char *mem)
{
	while (*(*s) && !ft_check_in(set, *(*s)))
	{
		if (*(*s) == '"' || *(*s) == '\'')
		{
			*mem = *(*s);
			if (*(*s))
				(*s)++;
			while (*(*s) != *mem && *(*s))
			{
				if (*(*s) == '\\' && *mem == '"')
					(*s)++;
				(*s)++;
			}
		}
		if ((*(*s)) == '\\')
			(*s)++;
		if (*(*s))
			(*s)++;
	}
}

char			**ft_set_split(char *s, char *set, char *keep)
{
	char	*last;
	char	**strs;
	char	**k;
	char	mem;

	if (!s || !(strs = ft_calloc_bis(count_size(s, set, keep)
	+ 1, sizeof(char*))))
		return (0);
	k = strs;
	while (*s)
	{
		while (*s && ft_check_in(set, *s))
		{
			need_line(keep, &s, &k);
			s++;
		}
		last = s;
		split_help(&s, set, &mem);
		if (*last && !(*k = ft_calloc_bis(1, (s - last + 1) * sizeof(char))))
			return (freebuffs(strs));
		ft_memcpy(*k, last, s - last);
		k++;
	}
	return (strs);
}
