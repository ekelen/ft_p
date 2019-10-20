/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:43:59 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:53 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

/*
** Return one nvt line
*/

static char		*get_first_lines(char *s, size_t i)
{
	if (i == 0)
		return (NULL);
	if (i > 0 && s[i] == '\n' && s[i - 1] == '\r')
		return (ft_strndup(s, i + 1));
	return (get_first_lines(s, i - 1));
}

/*
** Copy, convert, write one nvt line
*/

void			write_first_lines(int fd, t_file_info *file_info)
{
	char		*first_lines;
	char		*content;

	first_lines = get_first_lines(file_info->content, file_info->len - 1);
	if (first_lines != NULL)
	{
		file_info->len -= ft_strlen(first_lines);
		file_info->content = ft_strndup(file_info->content +
			ft_strlen(first_lines), file_info->len);
		content = nvt_to_unix(first_lines);
		write(fd, content, ft_strlen(content));
		free(content);
	}
}

/*
** read, store, write, and free NVT-ASCII file contents
*/

void			store_ascii_file(int sockd, int fd)
{
	t_file_info	file_info;
	char		*tmp;
	int			r;
	char		buf[BUF_SIZE];

	file_info.content = NULL;
	file_info.len = 0;
	while ((r = recv(sockd, buf, BUF_SIZE, 0)) > 0)
	{
		tmp = file_info.content;
		file_info.content = malloc(file_info.len + r);
		if (tmp != NULL)
		{
			ft_memcpy(file_info.content, tmp, file_info.len);
			free(tmp);
		}
		ft_memcpy(file_info.content + file_info.len, buf, r);
		file_info.len += r;
		write_first_lines(fd, &file_info);
	}
	write(fd, file_info.content, file_info.len);
	free(file_info.content);
}

/*
** copy/convert, send, free ASCII data
*/

void			send_ascii_data(int sockd, char *content)
{
	char	*nvt_content;

	if (!(nvt_content = unix_to_nvt(content)))
	{
		ft_putendl_fd("[Error] Could not convert file to NVT ASCII.", 2);
		return ;
	}
	send(sockd, nvt_content, ft_strlen(nvt_content), 0);
	free(nvt_content);
}
