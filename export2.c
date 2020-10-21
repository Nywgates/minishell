/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 08:21:26 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/21 15:38:00 by user42           ###   ########.fr       */
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

void		help_export(char *arg, char **argument, int i, char ***env)
{
	int	n;

	n = 0;
	if ((n = find_arg(arg, *env)))
	{
		if (valid_ass(argument[i]))
		{
			free((*env)[n]);
			(*env)[n] = ft_substr(argument[i], 0, ft_strlen(argument[i]));
		}
	}
	else
	{
		n = 0;
		while (n < get_size(*env))
			n++;
		(*env)[n] = ft_substr(argument[i], 0, ft_strlen(argument[i]));
		(*env)[n + 1] = NULL;
	}
}

void		ft_error_export(char **argument, int i)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argument[i], 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	g_stt = 1;
}

int			print_export(char **argument, int fd, char ***env)
{
	int		i;
	char	*arg;

	i = 0;
	g_stt = 0;
	while (argument[i])
	{
		if (!ft_strncmp(argument[i], "export", 6)
			&& ft_strlen(argument[i]) == 6)
			break ;
		i++;
	}
	if (argument[i] && (!argument[i + 1]
		|| argument[i + 1][0] == '\0' || argument[i + 1][0] == '|'))
		return (ft_alphabet(*env, get_size(*env), fd));
	while (argument[++i] && argument[i][0] != '|')
	{
		arg = get_arg(argument[i]);
		if (!check_arg(arg))
			ft_error_export(argument, i);
		else
			help_export(arg, argument, i, env);
		free(arg);
	}
	return (1);
}
