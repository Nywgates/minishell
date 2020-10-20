/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:01:01 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/20 10:45:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_fd(char **argument, t_var *fd)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (argument[++i])
	{
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

int		count_pipe(char **argument)
{
	int i;
	int n;

	i = 0;
	n = 0;
	while (argument[i])
	{
		if (argument[i][0] == '|')
			n++;
		i++;
	}
	n++;
	return (n);
}

char	**get_env(char *name, char **env)
{
	int			i;
	char		**arg;

	i = -1;
	while (env[++i])
	{
		arg = ft_split(env[i], '=');
		if (!ft_strncmp(arg[0], name, ft_strlen(name))
		&& ft_strlen(name) == ft_strlen(arg[0]))
			return (arg);
		free_dbl_ptr(arg);
	}
	return (NULL);
}
