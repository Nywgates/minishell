/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gest_fd2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 14:01:01 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/20 09:55:48 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		help_chev_r(int j, char **aux, t_var *fd, int n)
{
	if (aux[j][1] == '>' && aux[j][2] == '>')
	{
		free_dbl_ptr(aux);
		return (ft_error(
			"minishell: syntax error near unexpected token `>>'\n", -2));
	}
	else if (aux[j + 1] && aux[j][1] != '>')
		fd->fd_out[n] = open(aux[j + 1], O_RDWR | O_CREAT | O_TRUNC, 0660);
	else if (aux[j + 1] && aux[j][0] == '>')
		fd->fd_out[n] = open(aux[j + 1], O_RDWR | O_APPEND | O_CREAT, 0660);
	else
	{
		free_dbl_ptr(aux);
		return (-1);
	}
	return (0);
}

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

int		chev_r_after_quote(char **argument, int i, t_var *fd, int n)
{
	int		j;
	char	**aux;
	int		ret;

	j = 0;
	ret = 0;
	aux = ft_split(argument[i], ' ');
	while (aux[j] && aux[j][0] != '>')
		j++;
	if (aux[j] && aux[j][0] == '>')
	{
		if (fd->fd_out[n] >= 0)
			close(fd->fd_out[n]);
		free(argument[i]);
		argument[i] = ft_substr(aux[0], 0, ft_strlen(aux[0]));
		ret = help_chev_r(j, aux, fd, n);
		if (ret == -2)
			return (-2);
		else if (ret == -1)
			return (-1);
	}
	free_dbl_ptr(aux);
	return (i);
}
