/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:43:28 by laballea          #+#    #+#             */
/*   Updated: 2020/10/16 13:52:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free(char **content, char *name, char *tmp)
{
	if (content)
	{
		free(content[0]);
		free(content[1]);
		free(content);
	}
	free(name);
	free(tmp);
}

void		dollar_var(char **arg, int i, int n, char **env)
{
	char	*tmp;
	char	*tmp2;
	char	**content;
	char	*name;

	name = get_name(&(arg[i])[n + 1]);
	content = get_env(name, env);
	if (content && arg[i][n + 1] != '"')
		tmp = ft_strjoin_free(ft_substr(arg[i], 0, n), content[1], 1);
	else
		tmp = ft_strjoin_free(ft_substr(arg[i], 0, n), "\0", 1);
	tmp2 = ft_strjoin_free(tmp, ft_substr(arg[i], n + ft_strlen(name) + 1, ft_strlen(&arg[i][n + ft_strlen(name)])), 2);
	ft_free(content, name, tmp);
	free(arg[i]);
	arg[i] = tmp2;
}

void		ft_env2(char **arg, int i, int n, char **env)
{
	if (arg[i][n + 1] == '0')
		dollar_zero(arg, i, n);
	else if (arg[i][n + 1] == '#')
		dollar_dieze(arg, i, n);
	else if (arg[i][n + 1] == '?')
		dollar_inte(arg, i, n);
	else
		dollar_var(arg, i, n, env);
}

void		ft_env(char **arg, char **env)
{
	int		i;
	int		n;
	char	mem;

	i = -1;
	while (arg[++i])
	{
		n = -1;
		while (arg[i][++n])
		{
			if (arg[i][n] == '\'')
			{
				mem = arg[i][n++];
				while (arg[i][n] && arg[i][n] != mem)
					n++;
				if (!arg[i][n])
					break ;
			}
			if (arg[i][n] == '$' && arg[i][n + 1])
			{
				ft_env2(arg, i, n, env);
				n = -1;
			}
		}
	}
}

int			print_env(int fd, char ***environ)
{
	int			i;

	i = -1;
	while ((*environ)[++i])
	{
		ft_putstr_fd((*environ)[i], fd);
		ft_putstr_fd("\n", fd);
	}
	g_stt = 0;
	return (1);
}
