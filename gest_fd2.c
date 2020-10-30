/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:01:01 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/30 11:58:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_dol(char **argument, int i, int n)
{
	char	*arg;
	char	**nsm;

	if ((argument[i][0] == '>' || argument[i][0] == '<') && argument[i + 1])
	{
		if ((argument[i + 1][0] == '>') && argument[i + 2])
			i++;
		n = 0;
		arg = del_quote(argument[i + 1]);
		if (ft_strlen(arg) == 0 || n == (int)ft_strlen(arg))
		{
			nsm = ft_set_split(g_nsm, " <>|", "<>|");
			ft_putstr_fd("bash: ", 2);
			if (ft_strlen(arg) == 0)
			{
				ft_putstr_fd(nsm[i + 1], 2);
				ft_putstr_fd(" :redirection ambiguë\n", 2);
			}
			free_dbl_ptr(nsm);
			free(arg);
			return (0);
		}
		free(arg);
	}
	return (1);
}

int		get_fd(char **argument, t_var *fd)
{
	int i;
	int n;

	i = -1;
	n = 0;
	while (argument[++i])
	{
		if (!check_dol(argument, i, 0))
			return (0);
		if (argument[i][0] == '|')
			n++;
		if ((i = chev_right(argument, i, fd, n)) == -1)
			break ;
		else if (i == -2)
			return (0);
		if ((i = chev_left(argument, i, fd)) == -1)
			break ;
		else if (i == -2)
			return (0);
	}
	return (1);
}

void	init_arg(char ***arg, char **env, int i, int n)
{
	(*arg) = malloc(sizeof(char *) * 3);
	(*arg)[0] = ft_substr(env[i], 0, n);
	(*arg)[1] = ft_substr(env[i], n + 1, ft_strlen(env[i]) - (n + 1));
	(*arg)[2] = NULL;
}

char	**get_env(char *name, char **env)
{
	int			i;
	int			n;
	char		**arg;

	i = -1;
	while (env[++i])
	{
		n = -1;
		while (env[i][++n])
		{
			if (env[i][n] == '=')
				break ;
		}
		if (env[i][n] == '=')
			init_arg(&arg, env, i, n);
		else
			arg = ft_split(env[i], '=');
		if (!ft_strncmp(arg[0], name, ft_strlen(name))
		&& ft_strlen(name) == ft_strlen(arg[0]))
			return (arg);
		free_dbl_ptr(arg);
	}
	return (NULL);
}

char	*del_quote(char *str)
{
	int		i;
	int		n;
	char	*tmp;
	int		t;

	t = 0;
	i = -1;
	ft_bzero(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))
	, ft_strlen(str) + 1);
	while (str[++i])
	{
		n = i;
		if (!skip(str, &i))
			break ;
		if (n != i)
		{
			while (++n < i)
				tmp[t++] = str[n];
		}
		if (!(str[i] == '"' || str[i] == '\''))
			tmp[t++] = str[i];
	}
	return (tmp);
}
