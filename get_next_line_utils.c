/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:56:00 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/26 09:51:42 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t size;

	size = 0;
	while (*str++)
		size++;
	return (size);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*dst;
	unsigned char	*str;
	size_t			n;

	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	if (!(dst = malloc(nmemb * size)))
		return (NULL);
	if (dst)
	{
		str = dst;
		n = nmemb * size;
		while (n != '\0')
		{
			*str = '\0';
			n--;
			str++;
		}
	}
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_calloc(1, 1));
	if (!(dst = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	if (start < ft_strlen(s))
	{
		while (s[i] && i < len)
		{
			dst[i] = s[start + i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *dst;
	char *ptr;

	if (!s1 || !s2)
		return (NULL);
	if (!(dst = malloc(sizeof(char)
		* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	ptr = dst;
	while (*s1)
		*dst++ = *s1++;
	while (*s2)
		*dst++ = *s2++;
	*dst = '\0';
	return (ptr);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return (char *)s;
		s++;
	}
	if (c == 0)
		return ((char *)s);
	return (0);
}
