/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:57:19 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/14 11:17:58 by qgimenez         ###   ########.fr       */
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
	(void)lst;
	if (filter_comp("unset", 5, argument[0]))
		g_stt = print_unset(argument, env);
	else if (filter_comp("exit", 4, argument[0]))
		ft_exit(argument);
	else if (filter_comp("export", 6, argument[0]) && !check_pipe(argument))
		print_export(argument, fd.fd_out[fd.pos], env);
	else if (filter_comp("cd", 2, argument[0]) && !check_pipe(argument))
		print_cd(argument);
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
		ft_quote1(lst, check_quote(lst));
		return (filter2(fd, argument, lst, env));
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

int		check_chev(char **argument)
{
	if (argument[0][0] == '>' || argument[0][0] == '<')
		write(1, "minishell: syntax error near unexpected token `newline'\n", 57);
	return (1);
}

int		filter(char *commande, char ***env)
{
	char	**argument;
	t_var	fd;
	int		i;
	t_lst	*lst;

	i = -1;
	argument = ft_set_split(commande, " <>|", "<>|");
	lst = NULL;
	ft_env(argument, *env);
	fd = fdp(argument);
	if (fd.error == 1)
		return (0);
	while (argument[++i])
	{
		if (ft_strncmp(argument[i], ">", 1))
			ft_lstadd_back(&lst, ft_lstnew(argument[i]));
		else
			while (argument[i] && !ft_strncmp(argument[i], ">", 1))
				i++;
		if (!argument[i] && check_chev(argument))
			break ;
	}
	ft_lstadd_back(&lst, NULL);
	filter2(fd, argument, lst, env);
	free_filter(argument, fd, lst);
	return (0);
}
