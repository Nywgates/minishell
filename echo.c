/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:32:20 by laballea          #+#    #+#             */
/*   Updated: 2020/10/14 11:45:58 by qgimenez         ###   ########.fr       */
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

void	help_echo(char **argument, t_var fd, int no, int i)
{
	while (argument[++i] && argument[i][0] != '|')
	{
		if (fd.fd_out[fd.pos] == 1)
			fdp_2(&fd, argument);
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
	char	**argument;

	i = 0;
	argument = transform_lst(lst);
	no = 0;
	if (argument[1] && !ft_strncmp(argument[1], "-n", 2)
		&& ft_strlen(argument[1]) == 2)
	{
		no = 1;
		i++;
	}
	help_echo(argument, fd, no, i);
	free_dbl_ptr(argument);
	g_stt = 0;
	return (0);
}
