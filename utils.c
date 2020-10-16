/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:09:27 by laballea          #+#    #+#             */
/*   Updated: 2020/10/16 09:39:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_in(char *str, char c)
{
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (n--)
		*destination++ = *source++;
	return (dst);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*mem;

	mem = (unsigned char *)s;
	while (n--)
	{
		*mem = '\0';
		mem++;
	}
}

int		ft_error(char *str, int ret)
{
	ft_putstr_fd(str, 1);
	return (ret);
}
