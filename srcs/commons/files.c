/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:21 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:21 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

void			store_bin_file(int sockd, int fd)
{
	int			r;
	char		buf[BUF_SIZE];

	while ((r = recv(sockd, buf, BUF_SIZE, 0)) > 0)
		write(fd, buf, r);
}

int				ft_chdir(const char *raw_dirname)
{
	int		status;
	char	*dirname;

	dirname = ft_strtrim(raw_dirname);
	status = chdir(dirname);
	ft_strdel(&dirname);
	return (status);
}

char			get_type_code(char *name, int i)
{
	if (g_available_types[i].name == NULL)
		return (0);
	if (ft_strcmp(g_available_types[i].name, name) == 0)
		return (g_available_types[i].code);
	return (get_type_code(name, i + 1));
}

bool			file_ok(char *path)
{
	int			fd;
	struct stat	buf;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	if (fstat(fd, &buf) == -1)
		return (false);
	close(fd);
	return ((buf.st_mode & S_IFMT) == S_IFREG);
}
