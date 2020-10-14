/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:19:02 by qgimenez          #+#    #+#             */
/*   Updated: 2020/03/12 17:01:43 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*del_quote(char *str)
{
	int		i;
	int		pos;
	int		pos2;
	char	mem;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			mem = str[i];
			pos = i;
			i++;
			while (str[i])
			{
				if (str[i] == mem)
				{
					pos2 = i - 2;
					while (str[i])
					{
						str[i] = str[i + 1];
						i++;
					}
					i = pos;
					while (str[i])
					{
						str[i] = str[i + 1];
						i++;
					}
					if (pos2 >= 0 && str[pos2])
					{
						i = pos2 - 1;
						mem = '\0';
						break ;
					}
					else
						return (NULL);
				}
				if (str[i])
					i++;
			}
		}
		if (str[i])
			i++;
	}
	return (str);
}
