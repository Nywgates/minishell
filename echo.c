/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:32:20 by laballea          #+#    #+#             */
/*   Updated: 2020/10/21 16:33:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_lstsize(t_lst *lst)
{
	int		i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**transform_lst(t_lst *lst)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		new[i++] = ft_substr(lst->maillon, 0, ft_strlen(lst->maillon) + 1);
		lst = lst->next;
	}
	new[i] = NULL;
	return (new);
}

void	skip_26(char ***argument, int i, int n)
{
	char *tmp;

	if ((*argument)[i][n] == 26 && (*argument)[i][n + 1] == '\0')
		(*argument)[i][n] = '\0';
	else
	{
		tmp = (*argument)[i];
		(*argument)[i] = ft_strjoin_free(ft_substr(tmp, 0, n),\
		ft_substr(tmp, n + 1, ft_strlen(tmp) - n), 3);
		free(tmp);
	}
}

void	help_echo(char **argument, t_var fd, int no, int i)
{
	int		n;

	while (argument[++i] && argument[i][0] != '|')
	{
		n = -1;
		while (argument[i][++n])
		{
			if (argument[i][n] == 26)
				skip_26(&argument, i, n);
			if (argument[i][n] == 11)
				argument[i][n] = '|';
		}
		if (!fd.error)
			ft_putstr_fd(argument[i], fd.fd_out[fd.pos]);
		if (argument[i + 1] && argument[i + 1][0] != '|')
			write(fd.fd_out[fd.pos], " ", 1);
	}
	if (!no && !fd.error)
		write(fd.fd_out[fd.pos], "\n", 1);
}

int		print_echo(t_lst *lst, t_var fd)
{
	int		i;
	int		no;
	int		n;
	char	**argument;

	i = 0;
	argument = transform_lst(lst);
	no = 0;
	while (argument[++i] && !ft_strncmp(argument[i], "-n", 2))
	{
		n = 0;
		while (argument[i][++n])
		{
			if (argument[i][n] != 'n')
				break ;
		}
		if (argument[i][n] != 'n' && argument[i][n])
			break ;
		else
			no = 1;
	}
	help_echo(argument, fd, no, --i);
	free_dbl_ptr(argument);
	g_stt = 0;
	return (0);
}
