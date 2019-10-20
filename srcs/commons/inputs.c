/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:25 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:26 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

static char	*join(char *s1, char *s2, unsigned int s1_len, unsigned int s2_len)
{
	char	*s;

	s = malloc(s1_len + s2_len);
	if (!s)
		exit_error(ALLOC_ERR);
	ft_memcpy(s, s1, s1_len);
	ft_strdel(&s1);
	ft_memcpy(s + s1_len, s2, s2_len);
	return (s);
}

char		*read_first_line(int fd)
{
	size_t			r;
	char			buf[INPUT_BUF_SIZE];
	char			*first_line;
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = 0;
	first_line = ft_strdup("");
	while ((r = read(fd, buf, INPUT_BUF_SIZE)) > 0)
	{
		len += r;
		first_line = join(first_line, buf, i, r);
		while (i < len)
		{
			if (i > 0 && first_line[i] == '\n' && first_line[i - 1] == '\r')
			{
				first_line[i - 1] = '\0';
				return (first_line);
			}
			i++;
		}
	}
	ft_strdel(&first_line);
	return (NULL);
}
