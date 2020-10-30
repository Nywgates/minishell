/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:14:15 by laballea          #+#    #+#             */
/*   Updated: 2020/10/30 12:00:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_new_line(char **arg, int i)
{
	if (arg[i][0] == '>' && arg[i + 1])
	{
		g_stt = 2;
		if (!arg[i + 1])
			return (ft_error("minishell: erreur de syntaxe près du symbole \
inattendu « newline »\n", -2));
		else if ((arg[i + 1][0] == '>' || arg[i + 1][0] == '<') && !arg[i + 2])
			return (ft_error("minishell: erreur de syntaxe près du symbole \
inattendu « newline »\n", -2));
	}
	return (1);
}

int		chev_right(char **arg, int i, t_var *fd, int n)
{
	char *tmp;

	if (arg[i][0] == '>' && arg[i + 1])
	{
		if (need_line_chev(arg, i) == -2)
			return (-2);
		if (fd->fd_out[n] >= 0)
			close(fd->fd_out[n]);
		if (arg[i + 2] && arg[i + 1][0] == '>' && arg[i + 2][0] == '>')
			return (ft_error(
				"minishell: syntax error near unexpected token `>>'\n", -2));
		else if (arg[i + 1][0] == '>' && arg[i + 2])
			chev_r_line(arg, &i, fd, n);
		else if (arg[i + 1] && arg[i + 1][0] != '>')
		{
			tmp = del_quote(arg[i++ + 1]);
			fd->fd_out[n] = open(tmp, O_RDWR | O_CREAT | O_TRUNC, 0660);
			free(tmp);
		}
		else
			return (-1);
	}
	else if (arg[i][0] == '>' && !arg[i + 1])
		return (inception_return());
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
				g_stt = 1;
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
