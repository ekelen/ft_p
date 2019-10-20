/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:38:36 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:38:37 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

/*
** Initialize client god struct
*/

t_client_handler	*init_cli_handler(void)
{
	t_client_handler *handler;

	handler = NULL;
	if (!(handler = (t_client_handler *)malloc(sizeof(t_client_handler))))
		return (ft_puterr_null(ALLOC_ERR));
	handler->dtp.addr = NULL;
	handler->dtp.port = -1;
	handler->dtp.socket = -1;
	handler->pi.addr = NULL;
	handler->pi.port = -1;
	handler->pi.socket = -1;
	handler->root = ".";
	handler->data_type_code = 'A';
	handler->dst_pathname = NULL;
	handler->src_pathname = NULL;
	ft_bzero(handler->current_command, 5);
	return (handler);
}

void				free_cli_handler(t_client_handler *handler)
{
	if (handler->dtp.addr)
		ft_strdel(&(handler->dtp.addr));
	if (handler->pi.addr)
		ft_strdel(&(handler->pi.addr));
	if (handler != NULL)
		free(handler);
}

int					handle_close_action(t_client_handler *h, char *msg)
{
	(void)msg;
	if (h->dtp.socket != -1)
		close(h->dtp.socket);
	if (h->pi.socket != -1)
		close(h->pi.socket);
	free_cli_handler(h);
	exit_error("Connection closed.");
	return (0);
}
