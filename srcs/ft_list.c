/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:34:59 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:36:56 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

t_list_dir	*ft_lstdirnew(char *name, t_filel *file)
{
	t_list_dir	*list;

	if (!(list = (t_list_dir *)malloc(sizeof(t_list_dir))))
		return (NULL);
	list->next = NULL;
	list->name = ft_strdup(name);
	list->file = file;
	return (list);
}

void		ft_lstdiradd(t_list_dir **alst, t_list_dir *new)
{
	if (!alst || !new)
		return ;
	if (alst)
		new->next = *alst;
	*alst = new;
}

int			ft_lstdirsize(t_list_dir *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void		ft_freelistdir(t_list_dir *lst)
{
	if (lst)
	{
		ft_freelistdir(lst->next);
		ft_strdel(&lst->name);
		ft_free_file(lst->file);
		free(lst);
		lst = NULL;
	}
}
