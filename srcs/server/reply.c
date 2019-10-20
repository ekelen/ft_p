/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reply.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:43 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:44 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

void	send_reply(t_server_handler *handler, char *reply)
{
	write(handler->pi.cs, reply, ft_strlen(reply));
}
