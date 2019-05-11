/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_ls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:53 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 12:03:58 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		ft_get_recursive(t_list_dir *lst, t_flagl *flag)
{
	while (lst)
	{
		if (lst->file && lst->file->mode[0] == 'd'
			&& !ft_end_by_dot(lst->file->name))
			ft_print_ls(flag, lst->file->d_name);
		lst = lst->next;
	}
}

static int		ft_test_list_err(t_list_dir *lst)
{
	int		ok;

	ok = 0;
	while (lst)
	{
		if (lst->file)
		{
			if (lst->file->mode[1] == 'r')
				ok++;
		}
		lst = lst->next;
	}
	return (ok);
}

static void		ft_printlistdir_extend(t_list_dir *lst, t_flagl *flag,
				t_size_file *size)
{
	ft_mergesort_lst(&lst, flag, flag->t ? &ft_mergecmp_time
					: &ft_mergecmp_name);
	if (flag->l && lst && ft_test_list_err(lst))
		ft_printf("total %llu\n", size->total);
	ft_print_list(lst, flag);
	if (flag->r_up)
		ft_get_recursive(lst, flag);
	ft_freelistdir(lst);
}

void			ft_set_size(t_size_file *size)
{
	size->group = 0;
	size->user = 0;
	size->block = 0;
	size->link = 0;
	size->size = 0;
	size->major = 0;
	size->total = 0;
}

void			ft_printlistdir(DIR *dir, t_flagl *flag, char *name,
				t_size_file *size)
{
	char				*tmp;
	t_list_dir			*lst;
	t_list_dir			*tmp_lst;
	struct dirent		*mydir;

	lst = NULL;
	ft_set_size(size);
	while ((mydir = readdir(dir)))
	{
		if (flag->a || (!flag->a && mydir->d_name[0] != '.'))
		{
			ft_lstdiradd(&lst, (tmp_lst = ft_lstdirnew(mydir->d_name,
				ft_stat(tmp = ft_strjoin(name, mydir->d_name), flag, 1, 1))));
			if (flag->l && tmp_lst->file)
			{
				ft_get_size_file(tmp_lst, size);
				size->total += tmp_lst->file->block_nb;
			}
			ft_strdel(&tmp);
		}
	}
	if (flag->l)
		ft_reformat_size_file(lst, size);
	ft_printlistdir_extend(lst, flag, size);
}
