/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:30:01 by laballea          #+#    #+#             */
/*   Updated: 2020/10/16 09:52:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		dollar_zero(char **arg, int i, int n)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_free(ft_substr(arg[i], 0, n), "minishell", 1);
	tmp2 = ft_strjoin_free(tmp, ft_substr(arg[i], n + 2,
	ft_strlen(&arg[i][n + 1])), 2);
	free(tmp);
	free(arg[i]);
	arg[i] = tmp2;
}

void		dollar_dieze(char **arg, int i, int n)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_free(ft_substr(arg[i], 0, n), "0", 1);
	tmp2 = ft_strjoin_free(tmp, ft_substr(arg[i], n + 2,
	ft_strlen(&arg[i][n + 1])), 2);
	free(tmp);
	free(arg[i]);
	arg[i] = tmp2;
}

void		dollar_inte(char **arg, int i, int n)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strjoin_free(ft_substr(arg[i], 0, n), ft_itoa(g_stt), 3);
	tmp2 = ft_strjoin_free(tmp, ft_substr(arg[i], n + 2,
	ft_strlen(&arg[i][n + 1])), 2);
	free(tmp);
	free(arg[i]);
	arg[i] = tmp2;
}

char		*get_name(char *str)
{
	int i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])))
		i++;
	return (ft_substr(str, 0, i));
}
