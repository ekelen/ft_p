/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_connection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:40:20 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:40:44 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

int			handle_password(t_client_handler *handler, char **args)
{
	char		command[CLI_DTP_BUFSIZE];
	char		*password;

	ft_bzero(command, CLI_DTP_BUFSIZE);
	if (ft_count_strs(args) != 1)
	{
		ft_putendl_fd("ERROR: Usage error: pass <password>.", 2);
		return (ERR_FMT);
	}
	password = ft_strtrim(args[0]);
	ft_strcpy(command, "PASS ");
	ft_strcat(command, password);
	ft_strdel(&password);
	ft_strcat(command, "\r\n");
	if (write(handler->pi.socket, command, ft_strlen(command)) < 0)
		exit_error("ERROR: Fatal error: Could not send password to server.");
	return (0);
}

int			handle_user(t_client_handler *handler, char **args)
{
	char *username;
	char command[CLI_DTP_BUFSIZE];

	if (ft_count_strs(args) != 1)
	{
		ft_putendl_fd("ERROR: Usage: user <username>", 2);
		return (ERR_FMT);
	}
	username = ft_strtrim(args[0]);
	ft_strcpy(command, "USER ");
	ft_strcat(command, username);
	ft_strdel(&username);
	ft_strcat(command, "\r\n");
	if (write(handler->pi.socket, command, ft_strlen(command)) < 0)
		exit_error("ERROR: Fatal error: Could not send USER \
		request to server.");
	return (0);
}
