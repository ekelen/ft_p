/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:12 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:12 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

/*
** Copy file contents into memory at *mapped_file
*/

static void		*map_file(int fd, off_t st_size)
{
	void	*mapped_file;

	mapped_file = NULL;
	mapped_file = mmap(NULL,
		st_size,
		PROT_READ | PROT_WRITE | PROT_EXEC,
		MAP_PRIVATE,
		fd,
		0);
	if (mapped_file == MAP_FAILED)
		return (NULL);
	return (mapped_file);
}

/*
** Open, get info, store, close file; send, free file contents
** Return 0 on success, else -1
*/

int				send_data_util(int sockd, char data_type_code, char *filename)
{
	char		*file_content;
	struct stat	buf;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (fstat(fd, &buf) == -1)
		return (-1);
	file_content = map_file(fd, buf.st_size);
	file_content = buf.st_size > 0 ? map_file(fd, buf.st_size) : "";
	if (file_content == NULL)
		return (-1);
	close(fd);
	if (data_type_code == 'A')
		send_ascii_data(sockd, file_content);
	else
		send(sockd, file_content, buf.st_size, 0);
	if (buf.st_size > 0)
		munmap(file_content, buf.st_size);
	return (0);
}

int				recv_data_util(int sockd, char data_type_code,
					char *dst_filename)
{
	int			fd;

	if ((fd = open(dst_filename, O_CREAT | O_RDWR, 0777)) < 0)
	{
		close(fd);
		return (int_error("Could not create new file"));
	}
	if (data_type_code == 'A')
		store_ascii_file(sockd, fd);
	else
		store_bin_file(sockd, fd);
	close(fd);
	return (0);
}
