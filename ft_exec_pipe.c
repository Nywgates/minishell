/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 09:52:51 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/14 08:57:02 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_var_pid(t_lst *lst, t_var var, char *my_path, char **flags)
{
	if (var.pid == 0 || (!lst->pipe && check_built_in(lst->maillon)))
	{
		exec_fils(lst, my_path, flags, var);
		if (lst->pipe)
			return (1);
	}
	return (0);
}

int		init_pipe(t_lst *lst, t_var *var)
{
	var->first++;
	lst->pipe = 0;
	return (1);
}

void	comp_pipe(t_lst *lst, t_var *var)
{
	if (lst->pipe || !check_built_in(lst->maillon))
	{
		pipe(var->fdright);
		var->pid = fork();
	}
	g_gpid = var->pid;
}

int		err_pipe(t_lst *lst, char **my_path)
{
	if (!(*my_path = env_path(lst)))
	{
		if (!ft_strncmp(lst->maillon, "|", 1))
		{
			g_stt = 258;
			return (ft_error("minishell: syntax error \
				near unexpected token `|'\n", 1));
		}
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd(lst->maillon, 1);
		return (ft_error(" :command not found\n", 1));
	}
	return (0);
}

int		exec_bin_pipe(t_lst *lst, t_var var, char ***env)
{
	char		*my_path;
	char		**flags;
	t_fils		*fiston;
	char		*name;

	fiston = NULL;
	my_path = NULL;
	init_var_exec(&var, env);
	while (lst && init_pipe(lst, &var))
	{
		if (err_pipe(lst, &my_path))
			return (1);
		flags = capture_the_flag(lst, my_path);
		comp_pipe(lst, &var);
		if (check_var_pid(lst, var, my_path, flags))
			exit(1);
		else if (var.pid != 0)
			ft_pidadd_back(&fiston, ft_pidnew(var.pid));
		name = lst->maillon;
		mouv_maillon(&lst, &var, my_path, flags);
		var.pos++;
	}
	ft_wait_pid(fiston, name);
	ft_pidclear(&fiston);
	return (0);
}
