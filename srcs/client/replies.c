/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:42:11 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:42:12 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

static char	*get_reply_message(char *reply)
{
	char *msg;

	if (ft_strlen(reply) > 4)
	{
		if (!(msg = ft_strdup(reply + 4)))
			return (ft_puterr_null("Unable to allocate for message (fatal)"));
	}
	else
		msg = NULL;
	return (msg);
}

static int	get_reply_code(char *reply)
{
	char	*tmp;
	int		code;

	if (!(tmp = ft_strsub(reply, 0, 3)))
		return ((int)ft_puterr_ret("No reply code found."));
	code = ft_atoi(tmp);
	ft_strdel(&tmp);
	return (code);
}

static int	handle_replies(t_client_handler *h, char *reply)
{
	char			*msg;
	unsigned int	reply_code;
	t_action		*action;

	reply_code = (unsigned int)get_reply_code(reply);
	msg = get_reply_message(reply);
	display_reply(reply_code, msg);
	action = get_action(reply_code, 0);
	if (action)
		(*action)(h, msg);
	ft_strdel(&msg);
	return (reply_code);
}

void		get_reply(t_client_handler *h)
{
	char	*reply;

	reply = read_first_line(h->pi.socket);
	reply = reply == NULL ? ft_strdup(REP_NOT_AVAILABLE) : reply;
	if (handle_replies(h, reply) == 0)
	{
		ft_strdel(&reply);
		reply = ft_strdup(REP_NOT_AVAILABLE);
		handle_replies(h, reply);
	}
	ft_strdel(&reply);
}
