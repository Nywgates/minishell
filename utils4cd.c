/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:31 by laballea          #+#    #+#             */
/*   Updated: 2020/10/26 12:16:28 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_home(void)
{
	char	*home;
	char	buf[100];
	int		i;

	i = 7;
	home = getcwd(buf, sizeof(buf));
	while (home[i])
	{
		if (home[i] == '/')
		{
			home[i] = '\0';
			break ;
		}
		i++;
	}
	return (ft_strjoin("", home));
}

static void	error(char *argument, char *path, char *home)
{
	int fd;

	ft_putstr_fd("minishell: cd: ", 2);
	if (argument[0] == '~' && argument[1] == '/')
		ft_putstr_fd(path, 2);
	else
		ft_putstr_fd(argument, 2);
	if ((fd = open(argument, O_RDWR, 0660)) != -1)
		ft_putstr_fd(": Not a directory\n", 2);
	else
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		if (fd >= 0)
			close(fd);
	}
	if (argument[0] == '~')
		free(path);
	free(home);
}

int			print_cd(t_lst *lst)
{
	char *home;
	char *path;
	char *arg;

	if (lst->next)
		arg = lst->next->maillon;
	else
		arg = NULL;
	home = get_home();
	if (!arg)
		chdir(home);
	else
	{
		path = arg;
		if (arg[0] == '~')
			path = ft_strjoin(home, &arg[1]);
		if (chdir(path) == -1)
		{
			error(arg, path, home);
			g_stt = 1;
			return (1);
		}
		if (arg[0] == '~')
			free(path);
	}
	free(home);
	g_stt = 0;
	return (1);
}

int			free_env(char **env, char *line)
{
	free(line);
	while (*env)
	{
		free(*env);
		env++;
	}
	return (0);
}
