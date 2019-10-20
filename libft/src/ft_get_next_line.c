/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:35:16 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:35:17 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	search(char **s, char **tmp, const int fd)
{
	int		r;
	char	buf[BUFSIZE + 1];
	char	*str;

	while (*tmp == NULL)
	{
		ft_strclr(buf);
		r = read(fd, buf, BUFSIZE);
		if (r < 0)
			return (-1);
		if (r == 0)
		{
			if ((*tmp = ft_strchr(*s, '\0')) == *s)
				return (0);
			return (1);
		}
		buf[r] = '\0';
		if (!(str = ft_strjoin(*s, buf)))
			return (-1);
		ft_strdel(s);
		*s = str;
		*tmp = ft_strchr(*s, '\n');
	}
	return (1);
}

int	get_next_line(const int fd, char **line)
{
	static char	*s = NULL;
	char		*tmp;
	int			status;

	if (fd < 0 || !line)
		return (-1);
	if (!s && !(s = ft_strnew(0)))
		return (-1);
	tmp = ft_strchr(s, '\n');
	status = search(&s, &tmp, fd);
	if (status < 0)
		return (-1);
	if (!(*line = ft_strsub(s, 0, tmp - s)))
		return (-1);
	if (!(tmp = ft_strdup(tmp + 1)))
		return (-1);
	free(s);
	s = tmp;
	return (status);
}
