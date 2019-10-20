/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filesystem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:31 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:32 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static int	list_dir(t_server_handler *handler, char **args)
{
	char	**default_params;
	int		res;

	default_params = ft_strsplit("/bin/ls .", ' ');
	(void)args;
	res = exec_builtin(handler, "/bin/ls", default_params);
	ft_strarr_del(&default_params);
	return (res);
}

void		handle_list(t_server_handler *handler, char **args)
{
	if (handler->mode == ACTIVE)
	{
		send_reply(handler, REP_ACTIVE_ERR);
		return ;
	}
	if (handler->dtp.cs != -1)
		send_reply(handler, REP_DTP_OPEN);
	else
	{
		send_reply(handler, REP_OPEN_DTP);
		handler->dtp.cs = create_cs(handler->dtp.socket);
	}
	if (list_dir(handler, args) == -1)
		send_reply(handler, REP_LIST_ERR);
	else
		send_reply(handler, REP_CLOSING_DTP);
	close(handler->dtp.cs);
	handler->dtp.cs = -1;
}

void		handle_pwd(t_server_handler *handler, char **args)
{
	char	*dirname;
	char	*absolute_path;
	char	*dst;

	(void)args;
	absolute_path = NULL;
	dst = NULL;
	absolute_path = getcwd(absolute_path, 0);
	if (absolute_path == NULL)
		exit(1);
	dirname = absolute_path + ft_strlen(handler->root);
	if ((dst = (char *)malloc(sizeof(char) *  \
		ft_strlen("257 \"") + ft_strlen(dirname) +
		ft_strlen("\" is your current location\r\n"))) == NULL)
		exit_error("Could not allocate space for dirname.");
	ft_strcpy(dst, "257 \"");
	if (*dirname)
		ft_strcat(dst, dirname);
	else
		ft_strcat(dst, "/");
	ft_strcat(dst, "\" is your current location\r\n");
	send_reply(handler, dst);
	ft_strdel(&absolute_path);
	ft_strdel(&dst);
}

void		handle_cwd(t_server_handler *handler, char **args)
{
	char	*startdir;
	char	*path;

	startdir = NULL;
	if (ft_count_strs(args) != 1 || !args[0])
	{
		send_reply(handler, REP_SYNTAX_ERR_ARGS);
		return ;
	}
	path = get_path(handler, args[0]);
	startdir = getcwd(startdir, 0);
	if (!check_path(handler, path) || chdir(path) == -1)
	{
		send_reply(handler, REP_ACTION_NOT_TAKEN);
		ft_strdel(&startdir);
		return ;
	}
	send_reply(handler, REP_FILE_ACT_OK);
}
