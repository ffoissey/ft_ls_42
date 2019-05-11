/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:35:20 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:37:10 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	ft_reformat_size_file(t_list_dir *lst, t_size_file *size)
{
	char	*fill;

	while (lst)
	{
		if (lst->file)
		{
			fill = ft_strnew_c(size->group - ft_strlen(lst->file->group), ' ');
			lst->file->group = ft_strjoinfree_n(&lst->file->group, &fill, BOTH);
			fill = ft_strnew_c(size->user - ft_strlen(lst->file->user), ' ');
			lst->file->user = ft_strjoinfree_n(&lst->file->user, &fill, BOTH);
			fill = ft_strnew_c(size->block - ft_strlen(lst->file->block), ' ');
			lst->file->block = ft_strjoinfree_n(&fill, &lst->file->block, BOTH);
			fill = ft_strnew_c(size->link - ft_strlen(lst->file->link), ' ');
			lst->file->link = ft_strjoinfree_n(&fill, &lst->file->link, BOTH);
			fill = ft_strnew_c(size->size - ft_strlen(lst->file->size), ' ');
			lst->file->size = ft_strjoinfree_n(&fill, &lst->file->size, BOTH);
			fill = ft_strnew_c(size->major - ft_strlen(lst->file->major), ' ');
			lst->file->major = ft_strjoinfree_n(&fill, &lst->file->major, BOTH);
		}
		lst = lst->next;
	}
}

void	ft_get_size_file(t_list_dir *lst, t_size_file *size)
{
	size_t	len;

	if ((len = ft_strlen(lst->file->user)) > size->user)
		size->user = len;
	if ((len = ft_strlen(lst->file->group)) > size->group)
		size->group = len;
	if ((len = ft_strlen(lst->file->size)) > size->size)
		size->size = len;
	if ((len = ft_strlen(lst->file->link)) > size->link)
		size->link = len;
	if ((len = ft_strlen(lst->file->block)) > size->block)
		size->block = len;
	if ((len = ft_strlen(lst->file->major)) > size->major)
		size->major = len;
}
