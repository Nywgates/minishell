/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:24:28 by user42            #+#    #+#             */
/*   Updated: 2020/10/30 10:20:36 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		filter_comp(char *str, size_t len, char *argument)
{
	if (!ft_strncmp(argument, str, len)
		&& ft_strlen(argument) == len)
		return (1);
	return (0);
}

void	filter_if(t_var fd, char **argument, t_lst *lst, char ***env)
{
	if (filter_comp("unset", 5, argument[0]))
		print_unset(lst, env);
	else if (filter_comp("export", 6, argument[0]) && !check_pipe(argument))
		print_export(lst, fd.fd_out[fd.pos], env);
	else if (filter_comp("cd", 2, argument[0]) && !check_pipe(argument))
		print_cd(lst);
	else if (filter_comp("env", 3, argument[0]) && !check_pipe(argument))
		print_env(fd.fd_out[fd.pos], env);
	else
	{
		exec_bin_pipe(lst, fd, env);
		if (fd.fd_out[fd.pos] != 1)
			close(fd.fd_out[fd.pos]);
	}
}

int		filter2(t_var fd, char **argument, t_lst *lst, char ***env)
{
	if (fd.error == 1)
		return (0);
	if (check_quote(lst))
	{
		ft_putstr_fd("multiple line call. It's a bonus.\n", 2);
		return (0);
	}
	del_quote_lst(lst);
	if (check_pipe(argument))
	{
		exec_bin_pipe(lst, fd, env);
		if (fd.fd_out[fd.pos] != 1)
			close(fd.fd_out[fd.pos]);
	}
	else
		filter_if(fd, argument, lst, env);
	g_gpid = 0;
	return (0);
}

void	free_filter(char **argument, t_var fd, t_lst *lst)
{
	free(fd.fd_out);
	free(fd.fd_in);
	free_dbl_ptr(argument);
	ft_lstclear(&lst);
}

void	filter(char *commande, char ***env)
{
	char	**argument;
	t_var	fd;
	int		i;
	t_lst	*lst;

	i = -1;
	argument = ft_set_split(commande, " <>|", "<>|");
	g_arg = argument;
	lst = NULL;
	ft_env(argument, *env);
	fd = fdp(argument);
	while (argument[++i])
	{
		if (ft_strlen(argument[i]) <= 0)
			continue;
		if (ft_strncmp(argument[i], ">", 1))
			ft_lstadd_back(&lst, ft_lstnew(argument[i]));
		else
			while (argument[i] && !ft_strncmp(argument[i], ">", 1))
				i++;
		if (!argument[i] && check_chev(argument))
			break ;
	}
	ft_lstadd_back(&lst, NULL);
	filter_bis(lst, fd, argument, env);
}
