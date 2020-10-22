/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:20:14 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/22 16:34:59 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipe(char **argument)
{
	int		i;

	i = 0;
	while (argument[i])
	{
		if (argument[i][0] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	get_environ(char ***env)
{
	int			i;
	extern char **environ;

	*env = environ;
	i = 0;
	while ((*env)[i])
	{
		(*env)[i] = ft_substr((*env)[i], 0, ft_strlen((*env)[i]));
		i++;
	}
	g_env = *env;
}

void	cmd(char *commande, char ***env)
{
	if (check_blank(commande, 0))
	{
		g_nsm = commande;
		if (commande)
			filter(commande, env);
		else
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd("", 1);
			ft_error(":command not found\n", 2);
		}
	}
}

int		check_error(char ***commande, char *line)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	if (!check_error_main(line))
		return (0);
	while (line[i])
	{
		if (!skip_quote(line, &i))
			break ;
		if (line[i] == ';')
		{
			n = i - 1;
			while (n > -1 && line[n] == ' ')
				n--;
			if (i == 0 || line[n] == ';' || line[n] == '|')
				return (error_token(line));
		}
		i++;
	}
	*commande = ft_split_mini(line, ';');
	g_cmd = *commande;
	free(line);
	return (1);
}

int		main(void)
{
	char		**commande;
	char		*line;
	int			retour;
	int			i;
	char		**env;

	get_environ(&env);
	signal(SIGINT, &sigint);
	signal(SIGQUIT, &signothing);
	ft_putstr_fd("minishell>", 1);
	g_gpid = 0;
	while ((retour = get_next_line(1, &line)) > 0)
	{
		if (!check_error(&commande, line))
			continue ;
		i = -1;
		while (commande[++i])
			cmd(commande[i], &env);
		free_dbl_ptr(commande);
		ft_putstr_fd("minishell>", 1);
	}
	ft_putstr_fd("exit\n", 1);
	exit(free_env(env, line));
	return (0);
}
