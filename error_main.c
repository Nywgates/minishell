/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 09:39:01 by user42            #+#    #+#             */
/*   Updated: 2020/10/26 10:16:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_blank(char *line, int b)
{
	int i;

	i = 0;
	while (line[i] == 32)
		i++;
	if ((size_t)i == ft_strlen(line))
	{
		if (b)
			write(1, "minishell>", 11);
		return (0);
	}
	return (1);
}

int		skip_quote(char *line, int *i)
{
	char mem;

	if (line[(*i)] == '\'' || line[(*i)] == '"')
	{
		mem = line[(*i)];
		(*i)++;
		while (line[(*i)] && line[(*i)] != mem)
			(*i)++;
		if (!line[(*i)])
			return (0);
	}
	return (1);
}

int		skip(char *line, int *i)
{
	if (line[(*i)] == '\\')
	{
		(*i)++;
		if (line[(*i)] && line[(*i) + 1])
			(*i)++;
	}
	if (!skip_quote(line, i))
		return (0);
	return (1);
}

int		check_chev_main(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == '>' || line[i] == '<') && line[i + 1] && line[i + 2])
		{
			if (line[i + 1] == ' ' && (line[i + 2] == '>'
			|| line[i + 2] == '<' || line[i + 2] == '|'))
			{
				ft_putstr_fd("bash: erreur de syntaxe près \
du symbole inattendu \"", 1);
				write(1, &line[i + 2], 1);
				ft_putstr_fd("\"\nminishell>", 1);
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

int		check_error_main(char *line)
{
	if (!check_blank(line, 1) || !check_chev_main(line)
	|| !check_pipe_main(line))
	{
		free(line);
		return (0);
	}
	return (1);
}
