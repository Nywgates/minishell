/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qgimenez <qgimenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 09:22:07 by qgimenez          #+#    #+#             */
/*   Updated: 2020/10/08 07:52:07 by qgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lst	*ft_lstnew(void *content)
{
	t_lst *element;

	if (!(element = malloc(sizeof(t_lst))))
		return (NULL);
	element->maillon = ft_substr(content, 0, ft_strlen(content));
	element->next = NULL;
	return (element);
}

void	ft_lstadd_back(t_lst **alst, t_lst *new)
{
	t_lst *tmp;

	if (!alst || !new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	ft_lstclear(t_lst **lst)
{
	t_lst	*tmp;
	t_lst	*supp;

	tmp = *lst;
	if (lst == NULL)
		return ;
	tmp = *lst;
	while (tmp)
	{
		supp = tmp;
		tmp = tmp->next;
		free(supp->maillon);
		free(supp);
	}
}
