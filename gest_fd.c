/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:14:15 by laballea          #+#    #+#             */
/*   Updated: 2020/10/20 10:11:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_new_line(char **arg, int i)
{
	if (arg[i][0] == '>' && arg[i + 1])
	{
		if (!arg[i + 1])
			return (ft_error("minishell: erreur de syntaxe près du symbole \
inattendu « newline »\n", -2));
		else if (arg[i + 1][0] == '>' && !arg[i + 2])
			return (ft_error("minishell: erreur de syntaxe près du symbole \
inattendu « newline »\n", -2));
	}
	return (1);
}

int		chev_right(char **arg, int i, t_var *fd, int n)
{
	if (arg[i][0] == '>' && arg[i + 1])
	{
		if (check_new_line(arg, i))
			return (-2);
		if (fd->fd_out[n] >= 0)
			close(fd->fd_out[n]);
		if (arg[i + 2] && arg[i + 1][0] == '>' && arg[i + 2][0] == '>')
			return (ft_error(
				"minishell: syntax error near unexpected token `>>'\n", -2));
		else if (arg[i + 1][0] == '>' && arg[i + 2])
		{
			fd->fd_out[n] = open(arg[i + 2], O_RDWR | O_APPEND | O_CREAT, 0660);
			i += 2;
		}
		else if (arg[i + 1] && arg[i + 1][0] != '>')
		{
			fd->fd_out[n] = open(arg[i++ + 1], O_RDWR | O_CREAT
			| O_TRUNC, 0660);
		}
		else
			return (-1);
	}
	else if (fd->fd_out[n] < 0)
		i = chev_r_after_quote(arg, i, fd, n);
	return (i);
}

int		chev_left(char **argument, int i, t_var *fd)
{
	if (argument[i][0] == '<')
	{
		if (argument[i + 1])
		{
			if ((fd->fd_in[fd->pos_in++] = open(argument[i + 1],
			O_RDWR, 0660)) == -1)
			{
				ft_putstr_fd("minishell: ", 1);
				ft_putstr_fd(argument[i + 1], 1);
				ft_putstr_fd(": No such file or directory\n", 1);
				fd->error = 1;
				return (-1);
			}
			i++;
		}
		else
			return (ft_error(
			"minishell: syntax error near unexpected token `newline'\n", -1));
	}
	return (i);
}

int		nbr_left(char **argument)
{
	int i;
	int result;

	result = 0;
	i = -1;
	while (argument[++i])
	{
		if (argument[i][0] == '<')
			result++;
	}
	return (result);
}

t_var	fdp(char **argument)
{
	t_var	fd;
	int		i;

	i = -1;
	fd.fd_out = malloc(sizeof(int) * (count_pipe(argument) + 1));
	fd.fd_out[0] = -2;
	while (++i < count_pipe(argument))
		fd.fd_out[i] = -2;
	fd.fd_in = malloc(sizeof(int) * (nbr_left(argument) + 1));
	fd.pos = 0;
	fd.pos_in = 0;
	fd.pid = 0;
	fd.error = 0;
	fd.argument = argument;
	if (!get_fd(argument, &fd))
		fd.error = 1;
	i = -1;
	while (++i < count_pipe(argument))
	{
		if (fd.fd_out[i] == -2)
			fd.fd_out[i] = 1;
	}
	g_fd = fd;
	return (fd);
}
