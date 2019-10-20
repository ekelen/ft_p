/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:30 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:31 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

size_t		ft_count_strs(char **s)
{
	size_t	nstrs;
	int		i;

	nstrs = 0;
	i = 0;
	while (s && s[i])
	{
		nstrs++;
		i++;
	}
	return (nstrs);
}

size_t		ft_count_words(char const *s, char c)
{
	size_t	nwords;
	size_t	is_start;
	int		i;

	nwords = 0;
	is_start = 0;
	i = 0;
	while (s[i])
	{
		if (*s != c && is_start == 0)
		{
			is_start = 1;
			nwords++;
		}
		if (*s == c && is_start == 1)
			is_start = 0;
		i++;
	}
	return (nwords);
}

void		ft_strarr_del(char ***strs)
{
	size_t	i;
	size_t	nstrs;
	char	*tmp;

	nstrs = ft_count_strs(*strs);
	i = -1;
	while (++i < nstrs)
	{
		tmp = (*strs)[i];
		ft_strdel(&tmp);
	}
	tmp = (*strs)[i];
	ft_strdel(&tmp);
	free(*strs);
	*strs = NULL;
	return ;
}
