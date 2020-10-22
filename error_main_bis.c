/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main_bis.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 09:51:14 by user42            #+#    #+#             */
/*   Updated: 2020/10/22 09:17:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error_token(char *line)
{
	write(1, "bash: syntax error near unexpected token ';'\n", 46);
	g_stt = 2;
	write(1, "minishell>", 11);
	free(line);
	return (0);
}

int		check_pipe_main(char *line)
{
	int i;
	int n;

	n = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
		{
			n = i - 1;
			while (n >= 0 && line[n] == ' ')
				n--;
			if (n < 0 || line[n] == ';' || line[n] == '|')
			{
				ft_putstr_fd("bash: erreur de syntaxe près \
du symbole inattendu « | »\nminishell>", 1);
				g_stt = 2;
				return (0);
			}
		}
		if (!skip(line, &i))
			break ;
		i++;
	}
	return (1);
}
