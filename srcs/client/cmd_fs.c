/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:40:51 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:40:52 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

int			handle_ls(t_client_handler *handler, char **args)
{
	if (ft_count_strs(args) != 0)
	{
		ft_putendl_fd("Usage error: ls takes no arguments.", 2);
		return (ERR_FMT);
	}
	if (handler->dtp.socket == -1)
	{
		if (handle_passive(handler, NULL) == 0)
			get_reply(handler);
	}
	if (write(handler->pi.socket, "LIST\r\n", ft_strlen("LIST\r\n")) < 0)
	{
		exit_error("Fatal error: Could not send LIST request to server.");
	}
	handler->dtp_action = handle_on_ok_to_ls;
	return (0);
}

int			handle_pwd(t_client_handler *handler, char **args)
{
	if (ft_count_strs(args) != 0)
	{
		ft_putendl_fd("Usage error: pwd takes no arguments.", 2);
		return (ERR_FMT);
	}
	if (write(handler->pi.socket, "PWD\r\n", ft_strlen("PWD\r\n")) < 0)
		exit_error("Fatal error: Could not send PWD request to server.");
	return (0);
}

int			handle_cd(t_client_handler *handler, char **args)
{
	char *dir_name;
	char command[CLI_DTP_BUFSIZE];

	if (ft_count_strs(args) != 1)
	{
		ft_putendl_fd("Usage error: cd <directory name>", 2);
		return (ERR_FMT);
	}
	dir_name = ft_strtrim(args[0]);
	ft_strcpy(command, "CWD ");
	ft_strcat(command, dir_name);
	ft_strdel(&dir_name);
	ft_strcat(command, "\r\n");
	if (write(handler->pi.socket, command, ft_strlen(command)) < 0)
		exit_error("Fatal error: Could not send CWD request to server.");
	return (0);
}
