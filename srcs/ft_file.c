/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:34:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:37:29 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void		ft_free_file(t_filel *file)
{
	if (!file)
		return ;
	ft_strdel(&file->mode);
	ft_strdel(&file->user);
	ft_strdel(&file->group);
	ft_strdel(&file->time);
	ft_strdel(&file->name);
	ft_strdel(&file->d_name);
	ft_strdel(&file->name_c);
	ft_strdel(&file->block);
	ft_strdel(&file->major);
	ft_strdel(&file->size);
	ft_strdel(&file->link);
	free(file);
	file = NULL;
}

void		ft_set_file(t_filel *file)
{
	file->mode = NULL;
	file->user = NULL;
	file->group = NULL;
	file->time = NULL;
	file->name = NULL;
	file->d_name = NULL;
	file->name_c = NULL;
	file->block = NULL;
	file->major = NULL;
	file->size = NULL;
	file->link = NULL;
}

static void	ft_retime(t_filel *file, int y_or_h)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strchr(file->time, ':');
	if (y_or_h == 0)
		*(tmp + 3) = '\0';
	else
	{
		tmp2 = ft_strdup(tmp + 6);
		*(file->time + (tmp - 2 - file->time)) = '\0';
		file->time = ft_strjoinfree_n(&file->time, &tmp2, BOTH);
		file->time[ft_strlen(file->time) - 1] = '\0';
	}
}

static void	ft_get_time(t_filel *file)
{
	unsigned long long	local;
	time_t				t;

	local = (unsigned long long)time(&t);
	if ((local + 3600 < file->timestamp || file->timestamp + 15724800 < local))
		ft_retime(file, 1);
	else
		ft_retime(file, 0);
}

void		ft_get_file(struct stat *sb, t_filel *file)
{
	struct passwd	*pass;
	struct group	*group;

	pass = getpwuid(sb->st_uid);
	group = getgrgid(sb->st_gid);
	file->link = ft_asprintf("%llu", (unsigned long long)sb->st_nlink);
	file->user = pass ? ft_strdup(pass->pw_name) : ft_strdup("\0");
	file->group = group ? ft_strdup(group->gr_name) : ft_strdup("\0");
	file->time = ft_strdup(ctime(&sb->st_mtime));
	ft_dup(&file->time, ft_strdup(ft_strchr(file->time, ' ')));
	file->size_nb = (unsigned long long)sb->st_size;
	ft_get_time(file);
	if (file->mode[0] == 'c' || file->mode[0] == 'b')
	{
		file->major = ft_asprintf("  %lu, ", major(sb->st_rdev));
		file->size = ft_asprintf("%lu", minor(sb->st_rdev));
	}
	else
	{
		file->major = ft_strdup(" ");
		file->size = ft_asprintf("%llu", (unsigned long long)sb->st_size);
	}
	file->block_nb = (unsigned long long)sb->st_blocks;
	file->block = ft_asprintf("%llu", (unsigned long long)sb->st_blocks);
}
