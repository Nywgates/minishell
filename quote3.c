/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:26:17 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/20 10:21:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote1(t_lst *lst, char *aux)
{
	char	*str;
	char	mem;

	mem = '\0';
	str = NULL;
	ft_quote(lst, aux, mem, str);
}

int		check_quote2(char *aux, int i)
{
	char mem;

	mem = '\0';
	if (aux[i] == '\'' || aux[i] == '"')
	{
		mem = aux[i];
		(i)++;
		while (aux[i] != mem && aux[i])
		{
			if (aux[i] == '\\' && mem != '\'')
				i += 2;
			else
				(i)++;
		}
		if (!aux[i])
			return (-1);
	}
	return (i);
}

char	*check_quote(t_lst *lst)
{
	int		i;
	char	*aux;

	while (lst)
	{
		i = 0;
		aux = lst->maillon;
		while (aux[i])
		{
			if (aux[i] == '\\')
			{
				if (aux[++i] != '\0')
					i++;
			}
			else
			{
				i = check_quote2(aux, i);
				if (i < 0)
					return (aux);
				i++;
			}
		}
		lst = lst->next;
	}
	return (NULL);
}

int		c(char c, char *tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	bs_dbquote2(int *i, char *mem, char *aux, int *n)
{
	(*i)++;
	*n = *i;
	while (aux[*i] != *mem && aux[*i])
	{
		if (aux[*i] == '|')
			aux[*i] = 11;
		if (aux[*i] == '\\' && *mem != '\'')
			*i += 2;
		else
			(*i)++;
	}
}
