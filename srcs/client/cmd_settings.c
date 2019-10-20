/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:40:59 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:40:59 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

int			handle_passive(t_client_handler *handler, char **args)
{
	if (ft_count_strs(args) != 0)
	{
		ft_putendl_fd("Usage error: passive takes no arguments.", 2);
		return (ERR_FMT);
	}
	if (write(handler->pi.socket, "PASV\r\n", ft_strlen("PASV\r\n")) < 0)
	{
		exit_error("Fatal error: Could not send PASV request to server.");
	}
	return (0);
}

int			handle_quit(t_client_handler *handler, char **args)
{
	if (ft_count_strs(args) != 0)
	{
		ft_putendl_fd("Usage error: quit takes no arguments.", 2);
		return (ERR_FMT);
	}
	if (write(handler->pi.socket, "QUIT\r\n", ft_strlen("QUIT\r\n")) < 0)
		exit_error("Fatal error: Could not send QUIT request to server.");
	return (0);
}

int			handle_type(t_client_handler *handler, char **args)
{
	char			command[CLI_DTP_BUFSIZE];
	unsigned int	strcount;
	char			code;

	ft_bzero(command, CLI_DTP_BUFSIZE);
	strcount = ft_count_strs(args);
	if (strcount != 1)
	{
		ft_putendl_fd("Usage error: type <binary|ascii|image>", 2);
		return (ERR_FMT);
	}
	code = get_type_code(args[0], 0);
	if (code == 0)
	{
		ft_putendl_fd("Usage error: type <binary|ascii|image>", 2);
		return (ERR_FMT);
	}
	handler->data_type_code = code;
	ft_strcpy(command, "TYPE ");
	ft_strcat(command, &code);
	ft_strcat(command, "\r\n");
	if (write(handler->pi.socket, command, ft_strlen(command)) < 0)
		exit_error("Fatal error: Could not send RETR request to server.");
	handler->dtp_action = handle_on_ok_to_put;
	return (0);
}
