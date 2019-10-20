/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_dtp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:37:07 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:37:41 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

static char	*get_formatted_address(char **input)
{
	int		i;
	char	*address;

	if ((address = malloc(17)) == NULL)
		return (ft_puterr_null(ALLOC_ERR));
	ft_bzero(address, 17);
	i = 0;
	while (i < 4)
	{
		if (!input[i])
			return (ft_puterr_null("ERROR: Invalid host provided by server."));
		ft_strcat(address, input[i]);
		if (i < 3)
			ft_strcat(address, ".");
		i++;
	}
	return (address);
}

static bool	create_client_dtp_2(t_client_handler *h)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_puterr_ret("ERROR: No protocol data found.\n"));
	h->dtp.socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(h->dtp.port);
	sin.sin_addr.s_addr = inet_addr(h->dtp.addr);
	if (connect(
		h->dtp.socket,
		(const struct sockaddr *)&sin,
		sizeof(sin)) == -1)
		return (ft_puterr_ret("ERROR: Could not establish \
		data connection to server.\n"));
	return (true);
}

/*
** Initiate data connection
** Return true if ok, false if err
*/

bool		create_client_dtp(t_client_handler *h, char *reply)
{
	char				*tmp;
	char				**addr;

	tmp = ft_strrchr(reply, '(') + 1;
	addr = ft_strsplit(tmp, ',');
	h->dtp.port = (ft_atoi(addr[4]) * 256) + ft_atoi(addr[5]);
	if (h->dtp.addr)
		ft_strdel(&(h->dtp.addr));
	if ((h->dtp.addr = get_formatted_address(addr)) == NULL)
		return (false);
	ft_strarr_del(&addr);
	if (h->dtp.addr == NULL)
		return (false);
	h->dtp.port = h->dtp.port;
	if (!create_client_dtp_2(h))
		return (false);
	put_client_connect_confirm(h->dtp.addr, h->dtp.port);
	return (true);
}
