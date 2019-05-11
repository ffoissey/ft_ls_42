/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 12:35:59 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void			ft_print_ls(t_flagl *flag, char *name)
{
	DIR			*dir;
	char		*tmp;
	t_size_file	size;

	if (flag->cur_nb)
		ft_printf("\n%s:\n", name);
	else if (flag->cur_nb || flag->err || flag->nb > 1)
		ft_printf("%s:\n", name);
	flag->cur_nb++;
	if ((dir = opendir(name)))
	{
		tmp = ft_strcmp(name, "/") ? ft_strjoin(name, "/") : ft_strdup(name);
		ft_printlistdir(dir, flag, tmp, &size);
		ft_strdel(&tmp);
		closedir(dir);
	}
	else
	{
		ft_transform_name(name);
		ft_dprintf(2, "ft_ls: %s: %s\n", name, strerror(errno));
		flag->err++;
	}
}

static void		ft_file_test_extend(t_list_dir *lst, t_flagl *flag,
				t_size_file *size)
{
	if (!lst)
		return ;
	if (flag->l)
		ft_reformat_size_file(lst, size);
	ft_mergesort_lst(&lst, flag, flag->t ? &ft_mergecmp_time
					: &ft_mergecmp_name);
	ft_print_list(lst, flag);
	ft_freelistdir(lst);
}

static void		ft_file_test(t_list_dir *lst, t_flagl *flag)
{
	t_list_dir	*list;
	t_list_dir	*tmp_list;
	t_filel		*f;
	char		*tmp;
	t_size_file	size;

	list = NULL;
	ft_set_size(&size);
	while (lst)
	{
		tmp = ft_strdup(lst->name);
		f = NULL;
		if ((f = ft_stat(tmp, flag, 0, 0)) && f->mode[0] != 'd'
			&& (f->mode[0] != 'l' || (flag->l && f->mode[0] == 'l')))
		{
			ft_lstdiradd(&list, (tmp_list = ft_lstdirnew(lst->name, f)));
			flag->l && tmp_list->file ? ft_get_size_file(tmp_list, &size) : 0;
			flag->cur_nb++;
		}
		else
			ft_free_file(f);
		ft_strdel(&tmp);
		lst = lst->next;
	}
	ft_file_test_extend(list, flag, &size);
}

static void		ft_process_ls(t_list_dir *lst, t_flagl *flag)
{
	t_list_dir	*tmp_lst;
	char		*tmp;
	t_filel		*file;

	tmp_lst = lst;
	while (lst)
	{
		file = NULL;
		tmp = ft_strdup(lst->name);
		if ((file = ft_stat(tmp, flag, 0, 1)) && file->mode[0] != 'd')
		{
			if (!flag->l && file->mode[0] == 'l')
				ft_print_ls(flag, lst->name);
		}
		else if (file && file->mode[0] == 'd')
			ft_print_ls(flag, lst->name);
		ft_free_file(file);
		ft_strdel(&tmp);
		lst = lst->next;
	}
	ft_freelistdir(tmp_lst);
}

int				main(int ac, char **av)
{
	t_flagl			flag;
	t_list_dir		*list;

	(void)ac;
	list = parse_arg(av + 1, &flag);
	if (list == NULL && !flag.err)
		ft_print_ls(&flag, ".");
	else
	{
		ft_mergesort_lst(&list, &flag, flag.t ? &ft_mergecmp_time
							: &ft_mergecmp_name);
		ft_file_test(list, &flag);
		ft_process_ls(list, &flag);
	}
	if (flag.err)
		return (1);
	return (0);
}
