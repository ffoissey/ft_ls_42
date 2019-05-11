/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:41 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 12:32:55 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void	ft_print_flag_one(t_list_dir *lst)
{
	while (lst)
	{
		if (lst->file)
			ft_putendl(lst->file->name_c);
		lst = lst->next;
	}
}

static void	ft_print_flag_m(t_list_dir *lst)
{
	struct winsize	w;
	size_t			len;

	if (ioctl(1, TIOCGWINSZ, &w) == -1)
	{
		ft_print_flag_one(lst);
		return ;
	}
	len = 0;
	while (lst)
	{
		if (len + ft_strlen(lst->file->name) + 2 > w.ws_col)
		{
			ft_putchar('\n');
			len = 0;
		}
		if (lst->next)
			len += ft_printf("%s, ", lst->file->name_c);
		else
			ft_putstr(lst->file->name_c);
		lst = lst->next;
	}
	ft_putchar('\n');
}

static void	ft_print_flag_o_or_g(t_list_dir *lst, t_flagl *flag)
{
	if (flag->g_low)
	{
		while (lst)
		{
			if (lst->file)
				ft_printf("%s %s %s %s%s%s %s\n", lst->file->mode,
						lst->file->link, lst->file->group, lst->file->major,
						lst->file->size, lst->file->time, lst->file->name_c);
			lst = lst->next;
		}
	}
	else
	{
		while (lst)
		{
			if (lst->file)
				ft_printf("%s %s %s %s%s%s %s\n", lst->file->mode,
						lst->file->link, lst->file->user, lst->file->major,
						lst->file->size, lst->file->time, lst->file->name_c);
			lst = lst->next;
		}
	}
}

static void	ft_print_flag_o_and_g(t_list_dir *lst)
{
	while (lst)
	{
		if (lst->file)
		{
			ft_printf("%s %s  %s%s%s %s\n", lst->file->mode,
					lst->file->link, lst->file->major,
					lst->file->size, lst->file->time, lst->file->name_c);
		}
		lst = lst->next;
	}
}

void		ft_print_list(t_list_dir *lst, t_flagl *flag)
{
	if (flag->g_low && flag->o_low)
		ft_print_flag_o_and_g(lst);
	else if (flag->g_low || flag->o_low)
		ft_print_flag_o_or_g(lst, flag);
	else if (flag->l)
	{
		while (lst)
		{
			if (lst->file)
			{
				ft_printf("%s %s %s  %s %s%s%s %s\n", lst->file->mode,
						lst->file->link, lst->file->user, lst->file->group,
						lst->file->major, lst->file->size, lst->file->time,
						lst->file->name_c);
			}
			lst = lst->next;
		}
	}
	else if (flag->one)
		ft_print_flag_one(lst);
	else if (flag->m)
		ft_print_flag_m(lst);
	else
		ft_normal_ls(lst);
}
