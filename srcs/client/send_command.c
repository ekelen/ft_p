/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:41:06 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:41:06 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

/*
** Lame version working with only one arg
*/

void	send_command(t_client_handler *handler, char *name, char *arg)
{
	char			command[CLI_DTP_BUFSIZE];

	ft_bzero(command, CLI_DTP_BUFSIZE);
	ft_strcpy(command, name);
	ft_strcat(command, " ");
	ft_strcat(command, arg);
	ft_strcat(command, "\r\n");
	if (write(handler->pi.socket, command, ft_strlen(command)) < 0)
		exit_error("ERROR: Could not send command to server.");
}
