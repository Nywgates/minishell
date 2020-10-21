/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:43:19 by user42            #+#    #+#             */
/*   Updated: 2020/10/21 15:57:38 by user42           ###   ########.fr       */
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
	free_dbl_ptr(flags);
	free(my_path);
	if (bl)
		ft_exit2(i);
}

int		ft_exit_need_line(char *tmp_str, int i, t_lst *lst)
{
	if (!ft_isdigit(tmp_str[i]))
	{
		ft_putstr_fd("bash: exit: ", 2);
		ft_putstr_fd(tmp_str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		if (!(!lst->pipe && g_lst->pipe))
			ft_exit2(2);
		else
		{
			g_stt = 2;
			return (0);
		}
	}
	return (1);
}

void	need_some_line(char *my_path, char **flags, t_lst *lst)
{
	if (lst->pipe)
	{
		free(my_path);
		free_dbl_ptr(flags);
	}
	if (!g_lst->pipe)
		ft_putstr_fd("exit\n", 1);
}

int		ft_exit(t_lst *lst, char *my_path, char **flags)
{
	int		i;
	char	*tmp_str;

	i = -1;
	need_some_line(my_path, flags, lst);
	tmp_str = (char *)lst->next->maillon;
	while (tmp_str[++i])
	{
		if (!ft_exit_need_line(tmp_str, i, lst))
			return (1);
	}
	if (lst->next->next && (g_stt = 1) == 1 &&
	ft_strncmp(lst->next->next->maillon, "|", 1))
		ft_putstr_fd("bash: exit: too many argument\n", 2);
	if (!lst->pipe && g_lst->pipe)
		g_stt = ft_atoi(tmp_str);
	else if (tmp_str)
		ft_exit2(ft_atoi(tmp_str));
	else
		ft_exit2(0);
	return (1);
}
