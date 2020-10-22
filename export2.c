/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 12:25:00 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 14:52:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			valid_ass(char *argument)
{
	int i;

	i = 0;
	while (argument[i])
	{
		if (argument[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void		help_export(char *arg, char *str, char ***env)
{
	int	n;

	n = 0;
	if ((n = find_arg(arg, *env)))
	{
		if (valid_ass(str))
		{
			free((*env)[n]);
			(*env)[n] = ft_substr(str, 0, ft_strlen(str));
		}
	}
	else
	{
		n = 0;
		while (n < get_size(*env))
			n++;
		(*env)[n] = ft_substr(str, 0, ft_strlen(str));
		(*env)[n + 1] = NULL;
	}
}

void		ft_error_export(char *str)
{
	ft_putstr_fd("minishell: export: « ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" » : not a valid identifier\n", 2);
	g_stt = 1;
}

int			print_export(t_lst *lst, int fd, char ***env)
{
	char	*arg;
	t_lst	*tmp;
	char	*aux;

	tmp = lst;
	g_stt = 0;
	aux = (char *)tmp->next;
	if (tmp->maillon && (!aux || aux[0] == '\0' || aux[0] == '|'))
		return (ft_alphabet(*env, get_size(*env), fd));
	while (tmp->next && aux[0] != '|')
	{
		tmp = tmp->next;
		aux = (char *)tmp->next;
		arg = get_arg(tmp->maillon);
		if (!check_arg(arg))
			ft_error_export(tmp->maillon);
		else
			help_export(arg, tmp->maillon, env);
		free(arg);
	}
	return (1);
}
