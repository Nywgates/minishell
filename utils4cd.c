/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 13:07:31 by laballea          #+#    #+#             */
/*   Updated: 2020/10/29 09:37:22 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_home(void)
{
	char	*home;
	char	buf[100];
	int		i;

	i = -1;
	while (++i < 100)
		buf[i] = '\0';
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

int			need_line_print_cd(char *arg, char *home)
{
	void	*o;
	char	*path;

	path = arg;
	if (arg && arg[0] == '~')
		path = ft_strjoin(home, &arg[1]);
	if (path && (o = opendir(path)) == NULL)
	{
		closedir(o);
		error(arg, path, home);
		g_stt = 1;
		return (0);
	}
	else if (path && g_lst->pipe <= 0)
		chdir(path);
	if (path)
		closedir(o);
	if (arg && arg[0] == '~')
		free(path);
	return (1);
}

int			print_cd(t_lst *lst)
{
	char *home;
	char *arg;

	if (lst->next && lst->next->next)
	{
		ft_putstr_fd("minishell: cd: trop d'arguments\n", 2);
		g_stt = 1;
		return (1);
	}
	if (lst->next && ft_strncmp((char *)lst->next->maillon, "|", 1))
		arg = lst->next->maillon;
	else
		arg = NULL;
	home = get_home();
	if (!arg && g_lst->pipe <= 0)
		chdir(home);
	else
	{
		if (!need_line_print_cd(arg, home))
			return (1);
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
