/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 13:05:37 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static t_filel	*ft_prepare_file(char *d_name, int format,
			t_flagl *flag, char *mode)
{
	t_filel			*file;
	struct winsize	w;

	if (ioctl(1, TIOCGWINSZ, &w) == -1)
		flag->g = 0;
	if (!(file = (t_filel *)malloc(sizeof(t_filel))))
		return (NULL);
	ft_set_file(file);
	if (d_name && d_name[0] == '/')
		file->name = ft_strdup(d_name + 1);
	else
		file->name = ft_strdup(d_name);
	file->d_name = ft_strdup(d_name);
	if (format)
		ft_transform_name(file->name);
	file->name_c = ft_strdup(file->name);
	file->size_name = ft_strlen(file->name);
	file->mode = ft_strdup(mode);
	if (flag->g)
		ft_color_name(file, mode);
	return (file);
}

t_filel			*ft_stat(char *d_name, t_flagl *flag, int call, int format)
{
	struct stat		sb;
	char			mode[12];
	t_filel			*file;

	if (lstat(d_name, &sb) == -1)
	{
		if (format)
			ft_transform_name(d_name);
		ft_dprintf(2, "ft_ls: %s: %s\n", d_name, strerror(errno));
		return (NULL);
	}
	ft_set_mode(mode, sb.st_mode);
	ft_xattr(d_name, mode);
	if ((call == 0 && format == 0 && mode[0] == 'd'))
		return (NULL);
	if (!(file = ft_prepare_file(d_name, format, flag, mode)))
		return (NULL);
	file->timestamp = sb.st_mtime;
	if (flag->l)
		ft_get_file(&sb, file);
	if (mode[0] == 'l')
		ft_symlink(d_name, file, flag);
	return (file);
}
