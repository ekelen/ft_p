/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_pi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:39:16 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 15:49:17 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

static char		*get_input(char *input, bool running)
{
	if (!running)
	{
		if (input != NULL)
			ft_strdel(&input);
		input = ft_strdup("quit");
	}
	return (input);
}

/*
** Main PI loop
*/

bool			on_connect_pi(t_client_handler *h)
{
	t_on_cli_command	*fn;
	char				*input;
	char				**split;
	int					gnl_ret;
	bool				running;

	running = true;
	get_reply(h);
	while (running)
	{
		ftp_display_prompt();
		if ((gnl_ret = get_next_line(0, &input)) == -1)
			return (false);
		input = get_input(input, gnl_ret > 0);
		running = ft_strcmp(input, "quit") != 0;
		split = ft_strsplit(input, ' ');
		fn = get_cmd_handler(h, split[0], 0);
		if (fn != NULL && ((*fn)(h, split + 1)) == OK_INT)
			get_reply(h);
		ft_strdel(&input);
		ft_strarr_del(&split);
	}
	return (true);
}

/*
** Initiate control connection
*/

bool			create_client_pi(t_client_handler *h, char *av[])
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				*address;
	struct hostent		*host;

	if ((proto = getprotobyname("tcp")) == 0)
		return (ft_puterr_ret("ERROR: No protocol data found."));
	host = gethostbyname(av[1]);
	if (host == NULL)
		return (ft_puterr_ret("ERROR: Unable to find host."));
	h->pi.socket = socket(PF_INET, SOCK_STREAM, proto->p_proto);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(av[2]));
	address = inet_ntoa(*(struct in_addr*)(host->h_addr_list[0]));
	sin.sin_addr.s_addr = inet_addr(address);
	if (connect(h->pi.socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
		return (ft_puterr_ret("ERROR: Unable to establish control \
		connection to server."));
	put_client_connect_confirm(h->pi.addr, h->pi.port);
	return (true);
}

bool			parse_connect_string(t_client_handler *h, char *av[])
{
	if (!(h->pi.addr = ft_strdup(av[1])))
		return (ft_puterr_ret("ERROR: Bad address."));
	if (!(h->pi.port = ft_atoi(av[2])) || h->pi.port < 1)
		return (ft_puterr_ret("ERROR: Bad port number."));
	return (true);
}
