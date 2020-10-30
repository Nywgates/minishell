/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:23:12 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/30 16:44:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mouv_maillon(t_lst **lst, t_var *var, char *my_path, char **flags)
{
	if (var->first > 1)
	{
		close(var->fdleft[0]);
		close(var->fdleft[1]);
	}
	while (lst[0] && (ft_strncmp(lst[0]->maillon, "|", 1)
		|| ft_strlen(lst[0]->maillon) != 1))
		lst[0] = lst[0]->next;
	if (lst[0] && (!ft_strncmp(lst[0]->maillon, "|", 1)
		&& ft_strlen(lst[0]->maillon) == 1))
		lst[0] = lst[0]->next;
	var->fdleft[0] = var->fdright[0];
	var->fdleft[1] = var->fdright[1];
	free(my_path);
	if (flags)
		free_dbl_ptr(flags);
}

void	init_var_exec(t_var *var, char ***env)
{
	var->first = 0;
	var->status = 0;
	var->pos = 0;
	var->fdleft[0] = -1;
	var->fdleft[1] = -1;
	var->fdright[0] = -1;
	var->fdright[1] = -1;
	var->env = (*env);
}

void	exit_trois_un(int i, char **flags, char *my_path, int bl)
{
	if (bl)
	{
		ft_pidclear(&g_fiston);
		g_stt = 127;
	}
	ft_exit3(i, flags, my_path, bl);
	exit(1);
}
