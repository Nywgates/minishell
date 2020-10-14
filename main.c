/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:20:14 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/08 15:34:32 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_pipe(char **argument)
{
	int i;

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
}

void	cmd(char *commande, char ***env)
{
	if (commande)
		filter(commande, env);
	else
	{
		ft_putstr_fd("minishell: ", 1);
		ft_putstr_fd("", 1);
		ft_error(":command not found\n", 2);
	}
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
		commande = ft_split_mini(line, ';');
		i = -1;
		while (commande[++i])
			cmd(commande[i], &env);
		free(line);
		free_dbl_ptr(commande);
		ft_putstr_fd("minishell>", 1);
	}
	ft_putstr_fd("exit\n", 1);
	exit(1);
	return (0);
}
