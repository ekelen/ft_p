/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:35 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:35 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

/*
** get_path returned pointer has to be freed
*/

char	*get_path(t_server_handler *handler, char *input)
{
	char	*path;

	path = NULL;
	if (*input == '/')
	{
		path = malloc(ft_strlen(input) + ft_strlen(handler->root) + 1);
		if (path == NULL)
			exit_error("Malloc error\n");
		ft_strcpy(path, handler->root);
		ft_strcat(path, input);
	}
	else
		path = ft_strndup(input, ft_strlen(input));
	return (path);
}

bool	check_path(t_server_handler *handler, char *path)
{
	char	*startdir;
	char	*dirname;
	bool	is_path_ok;

	startdir = NULL;
	startdir = getcwd(startdir, 0);
	dirname = NULL;
	if ((chdir(path)) == -1)
	{
		ft_strdel(&startdir);
		return (false);
	}
	dirname = getcwd(dirname, 0);
	is_path_ok = ft_strncmp(dirname, handler->root,
	ft_strlen(handler->root)) == 0;
	if ((chdir(startdir)) < 0)
		exit_error("Cannot move you back to auth'd directory.");
	ft_strdel(&startdir);
	ft_strdel(&dirname);
	return (is_path_ok);
}

char	*get_file_dir(char *filepath)
{
	int		i;
	char	*dirpath;

	dirpath = ft_strdup(filepath);
	i = ft_strlen(dirpath);
	while (i >= 0)
	{
		if (dirpath[i] == '/')
		{
			dirpath[i] = '\0';
			return (dirpath);
		}
		i -= 1;
	}
	return (dirpath);
}

bool	check_src_file_path(t_server_handler *handler, char *filepath)
{
	char	*dirpath;
	bool	path_ok;

	dirpath = get_file_dir(filepath);
	if (ft_strcmp(dirpath, filepath) == 0)
		path_ok = file_ok(filepath);
	else
		path_ok = check_path(handler, dirpath) && file_ok(filepath);
	ft_strdel(&dirpath);
	return (path_ok);
}

bool	check_dst_file_path(t_server_handler *handler, char *filepath)
{
	char	*dirpath;
	bool	path_ok;

	dirpath = get_file_dir(filepath);
	if (ft_strcmp(dirpath, filepath) == 0)
		path_ok = true;
	else
		path_ok = check_path(handler, dirpath);
	ft_strdel(&dirpath);
	return (path_ok);
}
