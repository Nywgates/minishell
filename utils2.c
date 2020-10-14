/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:58:18 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/08 10:24:06 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

char	*ft_strjoin_free(char *s1, char *s2, int num)
{
	char	*dst;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1 || !s2)
		return (NULL);
	if (!(dst = malloc(sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[++i])
		dst[i] = s1[i];
	while (s2[++j])
		dst[i++] = s2[j];
	dst[i] = '\0';
	if (num == 1)
		free(s1);
	if (num == 2)
		free(s2);
	if (num == 3)
		double_free(s1, s2);
	return (dst);
}

void	free_dbl_ptr(char **ptr)
{
	int i;

	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int		ft_exit(char **argument)
{
	int i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	while (argument[1] && argument[1][i])
	{
		if (!ft_isdigit(argument[1][i]))
		{
			ft_putstr_fd("bash: exit: ", 2);
			ft_putstr_fd(argument[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(255);
		}
		i++;
	}
	if (argument[1] && argument[2])
	{
		ft_putstr_fd("bash: exit: too many argument\n", 2);
		return (0);
	}
	if (argument[1])
		exit(ft_atoi(argument[1]));
	else
		exit(1);
}
