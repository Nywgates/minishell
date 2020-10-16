/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 09:39:01 by user42            #+#    #+#             */
/*   Updated: 2020/10/16 09:44:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_blank(char *line)
{
	int i;

	i = 0;
	while (line[i] == 32)
		i++;
	if ((size_t)i == ft_strlen(line))
	{
		write(1, "minishell>", 11);
		free(line);
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

int		error_token(char *line)
{
	write(1, "bash: syntax error near unexpected token ';'\n", 46);
	g_stt = 258;
	write(1, "minishell>", 11);
	free(line);
	return (0);
}
