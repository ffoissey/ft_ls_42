/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 10:36:07 by ffoissey          #+#    #+#             */
/*   Updated: 2019/02/05 10:36:09 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		ft_all_ok(char *mode)
{
	while (*mode)
	{
		if (*mode++ == '-')
			return (0);
	}
	return (1);
}

void	ft_transform_name(char *s)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
		i++;
	while (s[i] != '/' && i != 0)
		i--;
	if (i == 0)
		return ;
	i++;
	while (s[i])
		s[j++] = s[i++];
	s[j] = '\0';
}

void	ft_reformat(char *s)
{
	int		len;

	if (!s || !*s)
		return ;
	len = ft_strlen(s);
	if (s[len - 1] == '/')
		s[len - 1] = '\0';
}

int		ft_count_file(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int		ft_end_by_dot(char *s)
{
	int		len;

	if (!s || !*s)
		return (0);
	len = ft_strlen(s);
	if (s[len - 1] == '.')
		return (1);
	return (0);
}
