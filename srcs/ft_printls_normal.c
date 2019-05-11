/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printls_normal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/03/08 16:50:45 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static int	ft_getlen_normal(t_list_dir *lst, int *nb_elem)
{
	size_t			len;
	size_t			max_len;

	max_len = 0;
	while (lst)
	{
		if (lst->file && lst->file->name
			&& (len = ft_strlen(lst->file->name)) + 1 > max_len)
			max_len = len;
		if (lst->file)
			(*nb_elem)++;
		lst = lst->next;
	}
	return (max_len + 1);
}

static void	ft_reformat_normal(t_list_dir *lst, int max_len)
{
	char			*fill;

	while (lst)
	{
		if (lst->file)
		{
			fill = ft_strnew_c(max_len - ft_strlen(lst->file->name), ' ');
			lst->file->name_c = ft_strjoinfree_n(&lst->file->name_c,
										&fill, BOTH);
		}
		lst = lst->next;
	}
}

static int	ft_get_scale(t_list_dir *lst)
{
	size_t			max_len;
	struct winsize	w;
	int				col;
	int				nb_elem;

	nb_elem = 0;
	max_len = ft_getlen_normal(lst, &nb_elem);
	if (ioctl(1, TIOCGWINSZ, &w) == -1)
		return (nb_elem);
	ft_reformat_normal(lst, max_len);
	col = max_len ? w.ws_col / (max_len) : 1;
	return (nb_elem % col ? nb_elem / col + 1 : nb_elem / col);
}

void		ft_normal_ls(t_list_dir *lst)
{
	int				i;
	int				tmp_max;
	int				max;
	t_list_dir		*tmp;

	max = ft_get_scale(lst);
	tmp_max = 0;
	while (tmp_max < max)
	{
		tmp = lst;
		i = tmp_max;
		while (i && tmp)
		{
			tmp = tmp->next;
			i--;
		}
		while (tmp)
		{
			if (i++ % max == 0 && tmp->file)
				ft_putstr(tmp->file->name_c);
			tmp = tmp->next;
		}
		ft_putchar('\n');
		tmp_max++;
	}
}
