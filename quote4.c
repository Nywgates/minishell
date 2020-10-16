/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:27:30 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/16 21:45:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	bs_dbquote3(char **str, char **tmp, int *n)
{
	*tmp = ft_substr(*str, 0, (*n)++);
	*tmp = ft_strjoin_free(*tmp, ft_substr(*str, *n, ft_strlen(*str) - *n), 3);
	free(*str);
	*str = *tmp;
}

char	*bs_dbquote(char *aux, char *mem, int *i)
{
	char	*tmp;
	char	*str;
	int		n;

	*mem = aux[*i];
	bs_dbquote2(i, mem, aux, &n);
	if (*i - n != 0)
		tmp = ft_substr(aux, n, *i - n);
	else
		tmp = ft_strjoin("", "\032\0");
	(*i)++;
	str = tmp;
	if (*mem != '\'')
	{
		n = 0;
		while (str[n])
		{
			if (str[n] == '\\' && c(str[n + 1], "\\\""))
				bs_dbquote3(&str, &tmp, &n);
			else
				n++;
		}
	}
	return (tmp);
}

void	dedel2(char **res, char **aux, int *i)
{
	free(*res);
	*res = ft_substr(*aux, 0, *i);
	(*i)++;
	*res = ft_strjoin_free(*res, ft_substr(*aux, *i, ft_strlen(*aux) - *i), 3);
	free(*aux);
	*aux = ft_substr(*res, 0, ft_strlen(*res));
}

void	doodool(char **res, char **aux, char *mem, int *i)
{
	int n;

	free(*res);
	*res = ft_substr(*aux, 0, *i);
	*res = ft_strjoin_free(*res, bs_dbquote(*aux, mem, i), 3);
	n = ft_strlen(*res);
	*res = ft_strjoin_free(*res, ft_substr(*aux, *i, ft_strlen(*aux) - *i), 3);
	free(*aux);
	*aux = ft_substr(*res, 0, ft_strlen(*res));
	*i = n - 1;
}

char	*doodool2(char **res, char **aux)
{
	char	*tmp;

	if (ft_strlen(*res) == 0)
		tmp = ft_substr(*aux, 0, ft_strlen(*aux));
	else
		tmp = ft_substr(*res, 0, ft_strlen(*res));
	free(*aux);
	free(*res);
	return (tmp);
}
