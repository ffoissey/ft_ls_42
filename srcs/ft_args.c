/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:34:17 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 17:16:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		init_flag(t_flagl *flag)
{
	flag->a = 0;
	flag->l = 0;
	flag->r_low = 0;
	flag->r_up = 0;
	flag->g = 0;
	flag->c = 0;
	flag->g_low = 0;
	flag->o_low = 0;
	flag->one = 0;
	flag->t = 0;
	flag->nb = 0;
	flag->cur_nb = 0;
	flag->err = 0;
	flag->m = 0;
}

static void	ft_format_flag(char c, t_flagl *flag)
{
	if (c == 'C' || c == 'l' || c == 'm' || c == '1')
	{
		if (c != 'l')
		{
			flag->g_low = 0;
			flag->o_low = 0;
		}
		flag->one = c == '1' ? 1 : 0;
		flag->l = c == 'l' ? 1 : 0;
		flag->m = c == 'm' ? 1 : 0;
	}
	else if (c == 'o' || c == 'g')
	{
		flag->one = 0;
		flag->m = 0;
		if (c == 'o')
			flag->o_low = 1;
		if (c == 'g')
			flag->g_low = 1;
		flag->l = 1;
	}
}

static void	ft_flag_print(char c, t_flagl *flag)
{
	if (c == 'a')
		flag->a = 1;
	else if (c == 'r')
		flag->r_low = 1;
	else if (c == 't')
		flag->t = 1;
	else if (c == 'R')
		flag->r_up = 1;
	else if (c == 'G')
		flag->g = 1;
}

static void	ft_set_flag(char *s, t_flagl *flag, int *minus)
{
	if (*s == '-')
	{
		*minus = 1;
		s++;
	}
	while (*s)
	{
		if (!*minus && (*s == 'a' || *s == 'r' || *s == 't' || *s == 'R'
			|| *s == 'G'))
			ft_flag_print(*s, flag);
		else if (!*minus && (*s == 'C' || *s == 'l' || *s == 'm' || *s == '1'
				|| *s == 'o' || *s == 'g'))
			ft_format_flag(*s, flag);
		else
		{
			ft_dprintf(2, "ft_ls: illegal option -- %c\n", *minus ? '-' : *s);
			ft_dprintf(2, "usage: ft_ls [-CGRaglmort1] [file ...]\n");
			exit(1);
		}
		s++;
	}
}

t_list_dir	*parse_arg(char **av, t_flagl *flag)
{
	t_list_dir	*lst;
	t_filel		*file;
	int			minus;

	init_flag(flag);
	lst = NULL;
	minus = 0;
	while (*av && (*av)[0] == '-' && (*av)[1] && !minus)
		ft_set_flag(*av++ + 1, flag, &minus);
	ft_bubblesort_strtab(av);
	while (*av)
	{
		flag->nb++;
		file = ft_stat(*av, flag, 1, 0);
		if (file)
			ft_lstdiradd(&lst, ft_lstdirnew(*av, file));
		else
			flag->err++;
		av++;
	}
	return (lst);
}
