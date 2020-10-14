/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 15:59:38 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/12 16:13:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote(t_lst *lst, char *aux, char mem, char *str)
{
	char	*line;
	int		bool;

	bool = 0;
	g_sigbool = 0;
	while (lst && ft_strncmp(lst->maillon, aux, ft_strlen(aux)))
		lst = lst->next;
	help_quote(lst, &mem, &str);
	while (get_next_line(1, &line) > 0)
	{
		if (g_sigbool)
			break ;
		line = boobool(line, mem, &bool);
		str = ft_strjoin_free(str, line, 1);
		str = ft_strjoin_free(str, "\n", 1);
		if (bool)
			break ;
		else
			write(1, ">", 1);
		free(line);
	}
	free(line);
	free(lst->maillon);
	lst->maillon = ft_substr(str, 0, ft_strlen(str) - 1);
	free(str);
}

int		print_path(int fd)
{
	char	buf[100];

	ft_putstr_fd(getcwd(buf, sizeof(buf)), fd);
	ft_putstr_fd("\n", fd);
	g_stt = 0;
	return (1);
}

char	*del_char(char *str, char *mem)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			i += 2;
		else
		{
			if (str[i] == '\'' || str[i] == '"')
			{
				*mem = str[i];
				while (str[i])
				{
					str[i] = str[i + 1];
					i++;
				}
				i = 0;
			}
			else
				i++;
		}
	}
	return (str);
}

void	help_quote(t_lst *lst, char *mem, char **str)
{
	*str = ft_substr(lst->maillon, 0, ft_strlen(lst->maillon));
	*str = del_char(*str, mem);
	*str = ft_strjoin_free(*str, "\n", 1);
	write(1, ">", 1);
}

char	*boobool(char *line, char mem, int *bool)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == mem)
		{
			*bool = 1;
			while (line[i + 1])
			{
				line[i] = line[i + 1];
				i++;
			}
			line[i] = '\0';
		}
		else
			i++;
	}
	return (line);
}
