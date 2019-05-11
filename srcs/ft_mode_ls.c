/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:35 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:42:30 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

char		ft_file_type(int m)
{
	if ((m & 61440) == 49152)
		return ('s');
	if ((m & 61440) == 40960)
		return ('l');
	if ((m & 61440) == 32768)
		return ('-');
	if ((m & 61440) == 24576)
		return ('b');
	if ((m & 61440) == 16384)
		return ('d');
	if ((m & 61440) == 8192)
		return ('c');
	return ('p');
}

void		ft_set_mode(char *mode, int m)
{
	mode[0] = ft_file_type(m);
	mode[1] = (m & 256) ? 'r' : '-';
	mode[2] = (m & 128) ? 'w' : '-';
	mode[3] = (m & 64) ? 'x' : '-';
	if (m & 2048)
		mode[3] = mode[3] == 'x' ? 's' : 'S';
	mode[4] = (m & 32) ? 'r' : '-';
	mode[5] = (m & 16) ? 'w' : '-';
	mode[6] = (m & 8) ? 'x' : '-';
	if (m & 1024)
		mode[6] = mode[6] == 'x' ? 's' : 'S';
	mode[7] = (m & 4) ? 'r' : '-';
	mode[8] = (m & 2) ? 'w' : '-';
	mode[9] = (m & 1) ? 'x' : '-';
	if (m & 512)
		mode[9] = mode[9] == 'x' ? 't' : 'T';
	mode[10] = ' ';
	mode[11] = '\0';
}

void		ft_color_name(t_filel *file, char *mode)
{
	if (ft_all_ok(mode) && mode[0] != 'l')
		file->name_c = ft_strjoinfree("\033[30;43m", file->name_c, SECOND);
	else if (mode[3] == 's' || mode[3] == 'S')
		file->name_c = ft_strjoinfree("\033[30;41m", file->name_c, SECOND);
	else if (mode[6] == 's' || mode[6] == 'S')
		file->name_c = ft_strjoinfree("\033[30;46m", file->name_c, SECOND);
	else if (mode[0] == 'b')
		file->name_c = ft_strjoinfree("\033[34;46m", file->name_c, SECOND);
	else if (mode[0] == 'c')
		file->name_c = ft_strjoinfree("\033[30;43m", file->name_c, SECOND);
	else if (mode[0] == '-' && mode[3] == 'x')
		file->name_c = ft_strjoinfree("\033[31m", file->name_c, SECOND);
	else if (mode[0] == 's')
		file->name_c = ft_strjoinfree("\033[32m", file->name_c, SECOND);
	else if (mode[0] == 'p')
		file->name_c = ft_strjoinfree("\033[33m", file->name_c, SECOND);
	else if (mode[0] == 'd')
		file->name_c = ft_strjoinfree("\033[36m", file->name_c, SECOND);
	file->name_c = ft_strjoinfree(file->name_c, "\033[0m", FIRST);
}

void		ft_xattr(char *d_name, char *mode)
{
	char		xattr[1024];
	acl_t		acl;
	acl_entry_t	entry;

	acl = NULL;
	bzero(xattr, 1024);
	if (listxattr(d_name, xattr, 1024, XATTR_NOFOLLOW) > 0)
		mode[10] = '@';
	else if ((acl = acl_get_link_np(d_name, ACL_TYPE_EXTENDED)))
	{
		if (acl_get_entry(acl, ACL_FIRST_ENTRY, &entry) != -1)
			mode[10] = '+';
		acl_free(acl);
		acl = NULL;
	}
}

void		ft_symlink(char *d_name, t_filel *file, t_flagl *flag)
{
	char	tru[1025];

	bzero(tru, 1025);
	readlink(d_name, tru, 1024);
	if (flag->g)
	{
		file->name_c = ft_strjoinfree("\033[35m", file->name_c, SECOND);
		file->name_c = ft_strjoinfree(file->name_c, "\033[0m", FIRST);
	}
	if (flag->l)
	{
		file->name_c = ft_strjoinfree(file->name_c, " -> ", FIRST);
		file->name_c = ft_strjoinfree(file->name_c, tru, FIRST);
	}
}
