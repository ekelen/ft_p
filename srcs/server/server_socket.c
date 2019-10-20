/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:58 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:58 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

int	create_cs(int socket)
{
	int					cs;
	unsigned int		cslen;
	struct sockaddr_in	csin;

	cs = accept(socket, (struct sockaddr *)&csin, &cslen);
	if (cs == -1)
		exit_error("accept error");
	return (cs);
}

int	create_srv_socket(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	proto = getprotobyname("tcp");
	if (proto == 0)
		exit_error("getprotobyname error");
	sock = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		exit_error("bind error");
	return (sock);
}
