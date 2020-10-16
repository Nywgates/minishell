/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 09:16:16 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/16 17:40:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_clean(char **buf, int ret)
{
	free(*buf);
	*buf = 0;
	return (ret);
}

int		read_line(int fd, char **line)
{
	char	*save;
	int		ret;
	char	*buf;
	int		bl;

	bl = 0;
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1)))
		|| !(save = malloc(1)) || BUFFER_SIZE < 1)
		return (-1);
	*line = save;
	**line = 0;
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0 || bl)
	{
		buf[ret] = 0;
		save = ft_strjoin_free(save, buf, 1);
		*line = save;
		if (ft_strlen(*line) > 0)
			bl = 1;
		if (ft_strchr(buf, '\n'))
		{
			free(buf);
			return (ft_strlen(*line));
		}
	}
	return (rt_read(ret, &buf));
}

void	ft_save_copy(char **cursor, char **save, char **tmp, char **line)
{
	*cursor = *save;
	*save = ft_strjoin(*save, *tmp);
	free(*cursor);
	*line = ft_substr(*save, 0, ft_strlen(*save));
	free(*tmp);
}

int		find_pos(char *cursor, char *save)
{
	int i;

	i = 0;
	while (save[i] != *cursor)
		i++;
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char *save;
	char		*tmp;
	char		*cursor;
	int			ret;

	ret = 1;
	while (ret > 0)
	{
		if (fd < 0 || !line || BUFFER_SIZE < 1 ||
		!(save = !save ? ft_calloc(sizeof(char), 1) : save))
			return (-1);
		if ((cursor = ft_strchr(save, '\n')))
		{
			*line = ft_substr(save, 0, find_pos(cursor, save));
			tmp = save;
			save = ft_substr(save, find_pos(cursor, save) + 1, ft_strlen(save));
			free(tmp);
			return (g_save_ret(save));
		}
		ret = read_line(fd, &tmp);
		ft_save_copy(&cursor, &save, &tmp, line);
		if (ret > 0)
			free(*line);
	}
	return (ft_clean(&save, ret));
}
