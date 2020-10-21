/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 13:16:38 by laballea          #+#    #+#             */
/*   Updated: 2020/10/21 16:05:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		get_size(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		get_len(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int		in_env(char **env, char *name)
{
	int i;

	i = -1;
	while (++i < get_size(env))
	{
		if (!ft_strncmp(env[i], name, get_len(env[i])))
			return (i);
	}
	return (-1);
}

void	ft_new(char ***env, int ret)
{
	int i;

	i = -1;
	while (++i < get_size(*env))
	{
		if (i == ret)
		{
			while ((*env)[i])
			{
				if (i == ret)
					free((*env)[i]);
				(*env)[i] = (*env)[i + 1];
				i++;
			}
			(*env)[i] = NULL;
			break ;
		}
	}
}

int		print_unset(char **argument, char ***env)
{
	int			i;
	int			ret;

	i = 0;
	while (++i < get_size(argument))
	{
		if (!check_arg(argument[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(argument[i], 2);
	 		ft_putstr_fd("': not a valid identifier\n", 2);
			g_stt = 1;
		}
		else if ((ret = in_env(*env, argument[i])) != -1)
			ft_new(env, ret);
	}
	return (0);
}
