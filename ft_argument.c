/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argument.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 13:51:00 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/29 11:12:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**mem_no_flag(void)
{
	char	**no_flag;

	if (!(no_flag = malloc(sizeof(char *) * 2)))
		return (NULL);
	if (!(no_flag[0] = malloc(sizeof(char) * 1)))
		return (NULL);
	no_flag[0][0] = '\0';
	no_flag[1] = NULL;
	return (no_flag);
}

char	*first_wave(t_lst *tmp, char *my_path)
{
	char	*aux;
	char	*flag;

	flag = ft_substr(tmp->maillon, 0, ft_strlen(tmp->maillon));
	aux = ft_strjoin_free(my_path, "ę", 0);
	flag = ft_strjoin_free(aux, flag, 3);
	return (flag);
}

char	**second_wave(t_lst *lst, char *flag, char **no_flag)
{
	char	**test;

	lst->pipe = 1;
	test = ft_set_split(flag, "ę<", "");
	free(flag);
	free_dbl_ptr(no_flag);
	return (test);
}

char	**last_wave(char **no_flag, char *flag)
{
	int i;

	i = 0;
	free_dbl_ptr(no_flag);
	no_flag = ft_set_split(flag, "ę<", "");
	while (no_flag[i])
	{
		if (no_flag[i] && no_flag[i][0] == 26)
			no_flag[i][0] = '\0';
		i++;
	}
	free(flag);
	return (no_flag);
}

char	**capture_the_flag(t_lst *lst, char *my_path)
{
	t_lst	*tmp;
	char	*flag;
	char	**no_flag;
	char	*tmp_char;

	no_flag = mem_no_flag();
	tmp = lst;
	if (!tmp->next)
		return (no_flag);
	tmp = tmp->next;
	if (!ft_strncmp(tmp->maillon, "|", 1)
		&& (ft_strlen(tmp->maillon) == 1) && (lst->pipe = 1))
		return (no_flag);
	flag = first_wave(tmp, my_path);
	while (tmp->next)
	{
		tmp = tmp->next;
		if (!ft_strncmp(tmp->maillon, "|", 1) && ft_strlen(tmp->maillon) == 1)
			return (second_wave(lst, flag, no_flag));
		tmp_char = ft_strjoin_free(flag, "ę", 1);
		flag = ft_strjoin_free(tmp_char, tmp->maillon, 1);
	}
	replace_pipe(&flag);
	return (last_wave(no_flag, flag));
}
