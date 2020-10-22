/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4cdget.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 15:07:06 by laballea          #+#    #+#             */
/*   Updated: 2020/10/22 16:43:48 by user42           ###   ########.fr       */
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

int		need_line_chev(char **arg, int i)
{
	if (check_new_line(arg, i) == -2)
		return (-2);
	if (filter_comp("''", 2, arg[i + 1]))
	{
		g_stt = 1;
		return (ft_error("minishell: : No such file or directory\n", -2));
	}
	return (0);
}

int		inception_return(void)
{
	g_stt = 2;
	return (ft_error("minishell: erreur de syntaxe près du symbole \
inattendu « newline »\n", -2));
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
