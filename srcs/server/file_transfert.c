/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_transfert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:27 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:27 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static void		close_dtp(t_server_handler *handler)
{
	if (handler->dtp.cs != -1)
		close(handler->dtp.cs);
	handler->dtp.cs = -1;
}

static void		open_dtp(t_server_handler *handler)
{
	if (handler->dtp.cs != -1)
		send_reply(handler, REP_DTP_OPEN);
	else
	{
		send_reply(handler, REP_OPEN_DTP);
		handler->dtp.cs = create_cs(handler->dtp.socket);
	}
}

void			handle_stor(t_server_handler *handler, char **args)
{
	char	*path;

	if (handler->mode == ACTIVE)
	{
		send_reply(handler, REP_ACTIVE_ERR);
		return ;
	}
	path = get_path(handler, args[0]);
	if (!check_dst_file_path(handler, path))
	{
		send_reply(handler, REP_ACTION_NOT_TAKEN);
		close_dtp(handler);
		return ;
	}
	open_dtp(handler);
	if (recv_data_util(handler->dtp.cs, handler->data_type_code, path) == 0)
		send_reply(handler, REP_CLOSING_DTP);
	else
		send_reply(handler, REP_FILE_ISSUE);
	close_dtp(handler);
}

void			handle_retr(t_server_handler *handler, char **args)
{
	char	*path;

	if (handler->mode == ACTIVE)
	{
		send_reply(handler, REP_ACTIVE_ERR);
		return ;
	}
	path = get_path(handler, args[0]);
	if (!check_src_file_path(handler, path))
	{
		send_reply(handler, REP_ACTION_NOT_TAKEN);
		close_dtp(handler);
		return ;
	}
	open_dtp(handler);
	if (send_data_util(handler->dtp.cs, handler->data_type_code, path) == 0)
		send_reply(handler, REP_CLOSING_DTP);
	else
		send_reply(handler, REP_FILE_ISSUE);
	close(handler->dtp.cs);
	handler->dtp.cs = -1;
}
