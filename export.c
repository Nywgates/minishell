/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:32:19 by laballea          #+#    #+#             */
/*   Updated: 2020/10/17 14:54:01 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_envi(char **new, int fd, int len)
{
	int n;
	int i;

	i = -1;
	while (++i < len)
	{
		n = 0;
		ft_putstr_fd("declare -x ", fd);
		while (new[i][n] != '=' && new[i][n])
			write(fd, &new[i][n++], 1);
		if (new[i][n] == '=')
		{
			ft_putstr_fd("=\"", fd);
			while (new[i][++n])
				write(fd, &new[i][n], 1);
			ft_putstr_fd("\"", fd);
		}
		write(fd, "\n", 1);
	}
}

int			ft_alphabet(char **env, int len, int fd)
{
	char	**new;
	int		i;

	i = -1;
	new = malloc(sizeof(char*) * (len));
	while (++i < len)
		new[i] = env[i];
	i = -1;
	while (++i < len - 1)
	{
		if (ft_strncmp(new[i], new[i + 1], ft_strlen(new[i])) > 0)
		{
			ft_swap(&new[i], &new[i + 1]);
			i = -1;
		}
	}
	print_envi(new, fd, len);
	free(new);
	return (1);
}

char		*get_arg(char *argument)
{
	int i;

	i = 0;
	while (argument[i] && argument[i] != '=')
		i++;
	return (ft_substr(argument, 0, i));
}

int			check_arg(char *argument)
{
	int i;

	i = 0;
	if (!ft_isalpha(argument[0]) && argument[0] != '_')
		return (0);
	while (argument[i])
	{
		if (!ft_isalpha(argument[i]) && !ft_isdigit(argument[i])
		&& argument[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int			find_arg(char *arg, char **environ)
{
	int		i;
	char	*argenv;

	i = 0;
	while (environ[i])
	{
		argenv = get_arg(environ[i]);
		if (!ft_strncmp(argenv, arg, 6) && ft_strlen(argenv) == ft_strlen(arg))
		{
			free(argenv);
			return (i);
		}
		free(argenv);
		i++;
	}
	return (0);
}
