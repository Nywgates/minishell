/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 11:41:26 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/17 09:21:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_size(char const *s, char c)
{
	int i;
	int j;
	int n;

	j = 0;
	i = 0;
	n = 0;
	while (s[j])
	{
		if (s[j] != c && !n)
		{
			n++;
			i++;
		}
		if (s[j] == c)
			n = 0;
		j++;
	}
	return (i);
}

static int		add_word(char **dst, char const *curseur, char const *s, int j)
{
	int	i;

	i = 0;
	if (!(dst[j] = malloc(sizeof(char) * (curseur - s + 1))))
	{
		while (j-- > 0)
			free(dst[j]);
		free(dst);
		return (0);
	}
	while (s < curseur)
		dst[j][i++] = *s++;
	dst[j][i] = '\0';
	return (1);
}

char			**ft_split(char const *s, char c)
{
	int			j;
	char		**dst;
	char const	*curseur;

	if (!s)
		return (NULL);
	curseur = s;
	j = 0;
	if (!(dst = malloc(sizeof(char *) * (count_size(s, c) + 1))))
		return (NULL);
	dst[count_size(s, c)] = 0;
	while (*s)
	{
		while (*curseur != c && *curseur)
			curseur++;
		if (curseur - s > 0)
		{
			if (add_word(dst, curseur, s, j++) == 0)
				return (NULL);
			s = curseur;
		}
		if (*s++ == 0 || !curseur++)
			break ;
	}
	return (dst);
}

void			split_mini_help(char const **curseur,\
				char c, int *bool, char *mem)
{
	while (*(*curseur) && (*(*curseur) != c || (*bool)))
	{
		if ((*(*curseur) == '\\'))
		{
			if (++(*curseur) && (*(*curseur)) != '\0')
				(*curseur)++;
		}
		else
		{
			if (*(*curseur) == '\'' || *(*curseur) == '"')
			{
				*mem = *(*curseur);
				(*curseur)++;
				while (*(*curseur) && *(*curseur) != *mem)
				{
					if (*(*curseur) == '\\' && *mem == '"')
						(*curseur)++;
					(*curseur)++;
				}
				if (*(*curseur) == '\0')
					break ;
			}
			(*curseur)++;
		}
	}
}

char			**ft_split_mini(char const *s, char c)
{
	int			j;
	char		**dst;
	char const	*curseur;
	int			bool;
	char		mem;

	bool = 0;
	mem = '\0';
	if ((curseur = s) == NULL)
		return (NULL);
	j = 0;
	dst = ft_calloc((count_size_mini(s, c) + 1), sizeof(char *));
	while (*s)
	{
		split_mini_help(&curseur, c, &bool, &mem);
		if (curseur - s > 0)
		{
			if (add_word(dst, curseur, s, j++) == 0)
				return (NULL);
			s = curseur;
		}
		if (*s++ == 0 || !curseur++)
			break ;
	}
	return (dst);
}
