/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:40:55 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:40:56 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

int			close_dtp(t_client_handler *h, char *msg)
{
	(void)msg;
	if (h->dtp.socket == -1)
		close(h->dtp.socket);
	h->dtp.socket = -1;
	return (0);
}

int			handle_on_ok_to_get(t_client_handler *h)
{
	int		result;
	char	*dst_filename;

	if (!(dst_filename = (char *)ft_strrchr(h->dst_pathname, '/')))
		dst_filename = h->dst_pathname;
	result = recv_data_util(h->dtp.socket, h->data_type_code, dst_filename);
	if (result < 0)
		exit_error("[Fatal error]: could not open file.");
	close(h->dtp.socket);
	h->dtp.socket = -1;
	get_reply(h);
	return (result);
}

int			handle_on_ok_to_put(t_client_handler *h)
{
	int		result;
	char	*dst_filename;

	if (!(dst_filename = (char *)ft_strrchr(h->dst_pathname, '/')))
		dst_filename = h->dst_pathname;
	result = send_data_util(h->dtp.socket, h->data_type_code, h->src_pathname);
	if (result < 0)
		return (int_error("[Error]: could not open file."));
	close(h->dtp.socket);
	get_reply(h);
	h->dtp.socket = -1;
	return (result);
}

int			handle_on_ok_to_ls(t_client_handler *h)
{
	store_ascii_file(h->dtp.socket, 1);
	close(h->dtp.socket);
	h->dtp.socket = -1;
	get_reply(h);
	return (0);
}

int			handle_dtp_action(t_client_handler *h, char *msg)
{
	(void)msg;
	return (h->dtp_action(h));
}
