/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:31:44 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 17:58:40 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/xattr.h>
# include <dirent.h>
# include <stdlib.h>
# include <errno.h>
# include "libft.h"
# include <pwd.h>
# include <grp.h>
# include <sys/ioctl.h>
# include <sys/acl.h>

typedef struct			s_flagl
{
	int					nb;
	int					cur_nb;
	char				a;
	char				g;
	char				g_low;
	char				o_low;
	char				l;
	char				r_low;
	char				r_up;
	char				t;
	char				m;
	char				c;
	char				one;
	char				err;
	char				first;
}						t_flagl;

typedef struct			s_filel
{
	char				*mode;
	char				*link;
	char				*user;
	char				*group;
	char				*size;
	char				*time;
	char				*name;
	char				*d_name;
	char				*name_c;
	char				*major;
	char				*block;
	unsigned long long	size_nb;
	unsigned long long	size_name;
	unsigned long long	block_nb;
	unsigned long long	timestamp;
}						t_filel;

typedef struct			s_size_file
{
	size_t				user;
	size_t				group;
	size_t				block;
	size_t				major;
	size_t				link;
	size_t				size;
	size_t				total;
}						t_size_file;

typedef struct			s_list_dir
{
	struct s_list_dir	*next;
	t_filel				*file;
	char				*name;
}						t_list_dir;

t_list_dir				*parse_arg(char **av, t_flagl *flag);
t_filel					*ft_stat(char *d_name, t_flagl *flag,
						int stat, int format);
void					ft_free_file(t_filel *file);
void					ft_load_file(t_filel *filel, t_flagl *flag, char **s);
void					ft_printlistdir(DIR *dir, t_flagl *flag, char *name,
						t_size_file *size);
void					ft_reformat(char *s);
void					ft_transform_name(char *s);
int						ft_end_by_dot(char	*s);
void					ft_print_list(t_list_dir *lst, t_flagl *flag);
void					ft_get_file(struct stat *sb, t_filel *file);
void					ft_freelistdir(t_list_dir *lst);
void					ft_lstdiradd(t_list_dir **alst, t_list_dir *new);
int						ft_lstdirsize(t_list_dir *lst);
t_list_dir				*ft_lstdirnew(char *name, t_filel *file);
void					ft_set_file(t_filel *file);
void					ft_set_size(t_size_file *size);
void					ft_print_ls(t_flagl *flag, char *name);
void					ft_reformat_size_file(t_list_dir *lst,
						t_size_file *size);
void					ft_get_size_file(t_list_dir *lst, t_size_file *size);
void					ft_mergesort_lst(t_list_dir **lst, t_flagl *flag,
						int (*f)(t_list_dir *, t_list_dir *, t_flagl *flag));
int						ft_mergecmp_time(t_list_dir *a, t_list_dir *b,
						t_flagl *flag);
int						ft_mergecmp_name(t_list_dir *a, t_list_dir *b,
						t_flagl *flag);
int						ft_all_ok(char *mode);
char					ft_file_type(int m);
void					ft_set_mode(char *mode, int m);
void					ft_symlink(char *d_name, t_filel *file, t_flagl *flag);
void					ft_xattr(char *d_name, char *mode);
void					ft_color_name(t_filel *file, char *mode);
void					ft_normal_ls(t_list_dir *lst);

#endif
