/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 17:43:19 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 17:55:49 by user42           ###   ########.fr       */
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

void	ft_exit3(int i, char **flags, char *my_path)
{
	free_dbl_ptr(flags);
	free(my_path);
	ft_exit2(i);
}

void	filter_bis(t_lst *lst, t_var fd, char **argument, char ***env)
{
	g_lst = lst;
	filter2(fd, argument, lst, env);
	free_filter(argument, fd, lst);
}
