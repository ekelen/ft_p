/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:46:11 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:46:11 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static bool		is_valid_type(char type, int i)
{
	if (g_available_types[i].name == NULL)
		return (false);
	if (g_available_types[i].code == type)
		return (true);
	return (is_valid_type(type, i + 1));
}

void			handle_type(t_server_handler *handler, char **args)
{
	if (is_valid_type(*(args[0]), 0))
	{
		handler->data_type_code = *args[0];
		send_reply(handler, REP_OK);
	}
	else
		send_reply(handler, REP_ARGS_ISSUE);
}
