/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:58:50 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/12 15:36:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dedel(char *mem, char *aux)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(sizeof(char));
	res[0] = '\0';
	while (aux[i])
	{
		if (aux[i] == '\\')
			dedel2(&res, &aux, &i);
		else
		{
			if (aux[i] == '\'' || aux[i] == '"')
				doodool(&res, &aux, mem, &i);
			i++;
		}
		if ((size_t)i > ft_strlen(aux))
			break ;
	}
	return (doodool2(&res, &aux));
}

int		check_q(char *aux)
{
	int i;

	i = 0;
	while (aux[i])
	{
		if (aux[i] == '\\')
			i += 2;
		else
		{
			if (aux[i] == '\'' || aux[i] == '"')
				return (1);
			i++;
		}
	}
	return (0);
}

void	*del_quote_lst(t_lst *lst)
{
	char	mem;
	char	*tmp;

	while (lst)
	{
		mem = '\0';
		tmp = ft_substr(lst->maillon, 0, ft_strlen(lst->maillon));
		free(lst->maillon);
		lst->maillon = dedel(&mem, tmp);
		lst = lst->next;
	}
	return (NULL);
}
