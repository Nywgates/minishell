/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 07:59:40 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/30 14:59:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*test_path(char **my_path, t_lst *lst)
{
	int			i;
	char		*path;
	char		*tmp;
	struct stat	buf;

	i = 0;
	tmp = NULL;
	if ((stat(lst->maillon, &buf) == 0) || check_built_in(lst->maillon))
		return (ft_strjoin(lst->maillon, ""));
	else if (!my_path)
		return (NULL);
	path = ft_strjoin_free(my_path[i], "/", 0);
	tmp = ft_strjoin_free(path, lst->maillon, 1);
	while (my_path[i] && stat(tmp, &buf) != 0)
	{
		free(tmp);
		i++;
		path = ft_strjoin_free(my_path[i], "/", 0);
		tmp = ft_strjoin_free(path, lst->maillon, 1);
	}
	return (tmp);
}

char	*env_bis(t_lst *lst)
{
	char *path;

	path = test_path(NULL, lst);
	if (!path)
		return (NULL);
	else
		return (path);
}

char	*env_path(t_lst *lst)
{
	extern char **environ;
	char		**my_path;
	char		*path;
	int			i;
	int			j;

	if ((!ft_strncmp(lst->maillon, "export", 6) && ft_strlen(lst->maillon) == 6)
		|| (!ft_strncmp(lst->maillon, "unset", 5)
			&& ft_strlen(lst->maillon) == 5))
		return (ft_strjoin("", lst->maillon));
	i = 0;
	j = 0;
	while (environ[i] && ft_strncmp(environ[i], "PATH", 4))
		i++;
	if (!environ[i])
		return (env_bis(lst));
	while (environ[i][j] && environ[i][j] != '=')
		j++;
	j++;
	if (!environ[i][j])
		return (NULL);
	my_path = ft_split(&environ[i][j], ':');
	path = test_path(my_path, lst);
	free_dbl_ptr(my_path);
	return (path);
}
