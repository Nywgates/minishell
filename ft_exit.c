/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:43:19 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 15:29:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit2(int i)
{
	free_dbl_ptr(g_arg);
	ft_lstclear(&g_lst);
	free(g_fd.fd_out);
	free(g_fd.fd_in);
	free_dbl_ptr(g_cmd);
	free(g_save);
	while (*g_env)
	{
		free(*g_env);
		g_env++;
	}
	exit(i);
}

void	ft_exit3(int i, char **flags, char *my_path, int bl)
{
	if (flags)
		free_dbl_ptr(flags);
	free(my_path);
	if (bl)
		ft_exit2(i);
}

int		ft_exit_need_line(int i, t_lst *lst, char **flags, char *my_path)
{
	char *tmp_str;

	tmp_str = (char *)lst->next->maillon;
	if (!ft_isdigit(tmp_str[i]) && tmp_str[0] != '|')
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(tmp_str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (!(!lst->pipe && g_lst->pipe))
			ft_exit3(2, flags, my_path, 1);
		else
		{
			g_stt = 2;
			return (0);
		}
	}
	return (1);
}

void	need_some_line(int *i, char **tmp_str)
{
	*tmp_str = NULL;
	*i = -1;
	if (!g_lst->pipe)
		ft_putstr_fd("exit\n", 1);
}

int		ft_exit(t_lst *lst, char *my_path, char **flags)
{
	int		i;
	char	*tmp_str;

	need_some_line(&i, &tmp_str);
	if (lst->next && ft_strncmp((char *)lst->next->maillon, "|", 1))
		tmp_str = (char *)lst->next->maillon;
	while (tmp_str && lst->next && tmp_str[++i])
	{
		if ((tmp_str[i] == '-' || tmp_str[i] == '+') && i == 0)
			i++;
		if (!ft_exit_need_line(i, lst, flags, my_path))
			return (1);
	}
	if (tmp_str && lst->next->next && (g_stt = 1) == 1 &&
	ft_strncmp(lst->next->next->maillon, "|", 1))
		ft_putstr_fd("bash: exit: too many argument\n", 2);
	else if (!lst->pipe && g_lst->pipe)
		g_stt = (tmp_str == NULL ? g_stt : ft_atoi(tmp_str));
	else if (tmp_str)
		ft_exit3(ft_atoi(tmp_str), flags, my_path, 1);
	else
		ft_exit3(g_stt, flags, my_path, 1);
	return (1);
}
