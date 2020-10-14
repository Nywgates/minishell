/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4cdget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:07:06 by laballea          #+#    #+#             */
/*   Updated: 2020/02/12 11:03:34 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current(char *home)
{
	char	*tmp;
	char	*result;
	char	buf[100];
	int		i;

	i = 0;
	tmp = &getcwd(buf, sizeof(buf))[ft_strlen(home) + 1];
	if (ft_strlen(getcwd(buf, sizeof(buf))) == ft_strlen(home))
		return (NULL);
	else
	{
		if (!(result = malloc(sizeof(char) * (ft_strlen(tmp) + 1))))
			return (NULL);
		while (tmp[i])
		{
			result[i] = tmp[i];
			i++;
		}
	}
	result[i] = '\0';
	return (result);
}

char	*get_path(char *home, char *argument)
{
	char *path;
	char *tmp;
	char *current;

	current = get_current(home);
	path = ft_strjoin(home, "/");
	tmp = ft_strjoin(path, argument);
	free(path);
	if (!current)
	{
		free(current);
		return (tmp);
	}
	else
	{
		path = ft_strjoin(tmp, "/");
		free(tmp);
		tmp = ft_strjoin(path, current);
		free(path);
		free(current);
		return (tmp);
	}
}
