/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mergesort_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:28 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:39:36 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int					ft_mergecmp_name(t_list_dir *a, t_list_dir *b,
					t_flagl *flag)
{
	if (!a->name || !b->name)
		return (0);
	return (flag->r_low ? ft_strcmp(a->name, b->name) >= 0 :
			ft_strcmp(a->name, b->name) <= 0);
}

int					ft_mergecmp_time(t_list_dir *a, t_list_dir *b,
					t_flagl *flag)
{
	if (a->file && b->file)
	{
		if (a->file->timestamp < b->file->timestamp)
			return (flag->r_low ? 1 : 0);
		else if (a->file->timestamp > b->file->timestamp)
			return (flag->r_low ? 0 : 1);
		else
			return (ft_mergecmp_name(a, b, flag));
	}
	return (1);
}

static void			ft_mergesplit_lst(t_list_dir *head,
					t_list_dir **a, t_list_dir **b)
{
	t_list_dir	*fast;
	t_list_dir	*slow;

	slow = head;
	fast = head->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*a = head;
	*b = slow->next;
	slow->next = NULL;
}

static t_list_dir	*ft_process_merge(t_list_dir *a, t_list_dir *b,
			t_flagl *flag, int (*f)(t_list_dir *, t_list_dir *, t_flagl *flag))
{
	t_list_dir	*result;

	if (!a)
		return (b);
	if (!b)
		return (a);
	result = NULL;
	if (f(a, b, flag))
	{
		result = a;
		result->next = ft_process_merge(a->next, b, flag, f);
	}
	else
	{
		result = b;
		result->next = ft_process_merge(a, b->next, flag, f);
	}
	return (result);
}

void				ft_mergesort_lst(t_list_dir **lst, t_flagl *flag,
					int (*f)(t_list_dir *, t_list_dir *, t_flagl *flag))
{
	t_list_dir *head;
	t_list_dir *a;
	t_list_dir *b;

	head = *lst;
	if (!head || !head->next)
		return ;
	ft_mergesplit_lst(head, &a, &b);
	ft_mergesort_lst(&a, flag, f);
	ft_mergesort_lst(&b, flag, f);
	*lst = ft_process_merge(a, b, flag, f);
}
