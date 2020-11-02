/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:26:53 by user42            #+#    #+#             */
/*   Updated: 2020/11/02 10:11:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_bis(char **arg, int i, int *n, char **env)
{
	if (arg[i][*n] == '$' && arg[i][*n + 1])
	{
		ft_env2(arg, i, *n, env);
		*n = -1;
	}
}

void	ft_env_tri(char **arg, int i, int n, char **env)
{
	if (arg[i][n] == '$' && arg[i][n + 1])
	{
		if (ft_isdigit(arg[i][n + 1]) || ft_isalpha(arg[i][n + 1]) ||
		arg[i][n + 1] == '_' || arg[i][n + 1] == '?' || arg[i][n + 1] == '#')
			ft_env2(arg, i, n, env);
	}
}

int		ft_env_help(char **arg, int *i, int *n)
{
	if (arg[*i][*n] == '\\')
	{
		(*n)++;
		if (arg[*i][*n] && arg[*i][*n + 1] && (arg[*i][*n] == '\''
		|| arg[*i][*n] == '\"'))
			(*n)++;
		if (!arg[*i][*n])
			return (1);
	}
	return (0);
}

void	ft_env_helpbis(char **arg, int i, int *n, char **env)
{
	char	mem;

	mem = arg[i][(*n)++];
	while (arg[i][*n] && arg[i][*n] != mem)
	{
		if (mem == '\"')
			ft_env_tri(arg, i, *n, env);
		(*n)++;
	}
}
