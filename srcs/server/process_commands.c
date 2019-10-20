/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:38 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:39 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static t_builtin	*get_builtin(char *command_name, unsigned int i)
{
	if (g_command_handler_list[i].command_name == NULL)
		return (NULL);
	if (ft_strcmp(command_name, g_command_handler_list[i].command_name) == 0)
		return (&(g_command_handler_list[i].fn));
	return (get_builtin(command_name, i + 1));
}

void				handle_passive(t_server_handler *handler, char **args)
{
	char	reply[100];
	char	**addr;

	(void)args;
	addr = ft_strsplit(handler->dtp.address, '.');
	ft_strcpy(reply, REP_PASV);
	ft_strcat(reply, addr[0]);
	ft_strcat(reply, ",");
	ft_strcat(reply, addr[1]);
	ft_strcat(reply, ",");
	ft_strcat(reply, addr[2]);
	ft_strcat(reply, ",");
	ft_strcat(reply, addr[3]);
	ft_strcat(reply, ",");
	ft_strcat(reply, ft_itoa(handler->dtp.port / 256));
	ft_strcat(reply, ",");
	ft_strcat(reply, ft_itoa(handler->dtp.port % 256));
	ft_strcat(reply, ").");
	ft_strcat(reply, "\r\n");
	send_reply(handler, reply);
	handler->mode = PASSIVE;
	if (handler->dtp.cs == -1)
		handler->dtp.cs = create_cs(handler->dtp.socket);
}

void				handle_port(t_server_handler *handler, char **args)
{
	(void)args;
	send_reply(handler, REP_ACTIVE_ERR);
	handler->mode = ACTIVE;
}

void				handle_quit(t_server_handler *handler, char **args)
{
	(void)args;
	send_reply(handler, REP_CLOSING_CS_PI);
	if (handler->dtp.cs != -1)
		close(handler->dtp.cs);
	if (handler->pi.cs != -1)
		close(handler->dtp.cs);
	if (handler->dtp.socket != -1)
		close(handler->dtp.socket);
	if (handler->pi.socket != -1)
		close(handler->dtp.socket);
	free_handler(handler);
}

void				process_command(t_server_handler *handler,
					char *command_name, char **args)
{
	t_builtin	*fn;

	if (!handler->logged && command_needs_auth(command_name, 0))
	{
		send_reply(handler, REP_AUTH_ERROR);
		return ;
	}
	fn = get_builtin(command_name, 0);
	if (fn == NULL)
		send_reply(handler, REP_UNIMPLEMENTED_CMD);
	else
		(*fn)(handler, args);
}
