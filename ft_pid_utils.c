/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pid_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 15:20:56 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/30 09:41:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_fils	*ft_pidnew(pid_t pid)
{
	t_fils *element;

	if (!(element = malloc(sizeof(t_fils))))
		return (NULL);
	element->pid = pid;
	element->next = NULL;
	return (element);
}

void	ft_pidadd_back(t_fils **fiston, t_fils *new)
{
	t_fils *tmp;

	tmp = *fiston;
	if (!fiston || !new)
		return ;
	if (!*fiston)
	{
		*fiston = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_pidclear(t_fils **fiston)
{
	t_fils	*tmp;
	t_fils	*supp;

	tmp = *fiston;
	if (fiston == NULL)
		return ;
	tmp = *fiston;
	while (tmp)
	{
		supp = tmp;
		tmp = tmp->next;
		free(supp);
	}
}
