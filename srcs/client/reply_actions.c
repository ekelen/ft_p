/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:42:08 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:42:47 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

int			handle_on_agree_dtp(t_client_handler *h, char *msg)
{
	if (h->dtp.socket == -1)
	{
		if (!(create_client_dtp(h, msg)))
			return (ERR_INT);
	}
	return (OK_INT);
}

int			handle_on_quit(t_client_handler *h, char *msg)
{
	(void)msg;
	if (h->dtp.socket != -1)
		close(h->dtp.socket);
	if (h->pi.socket != -1)
		close(h->pi.socket);
	return (OK_INT);
}

t_action	*get_action(unsigned int reply_code, unsigned int i)
{
	if (g_reply_actions[i].code == 0)
		return (NULL);
	if (g_reply_actions[i].code == reply_code)
		return (&(g_reply_actions[i].action));
	return (get_action(reply_code, i + 1));
}
