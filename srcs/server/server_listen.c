/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_listen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:53 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:46:33 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static void	wait_for_commands(t_server_handler *handler)
{
	char	**split;
	char	*command;

	while (42)
	{
		command = read_first_line(handler->pi.cs);
		if (command == NULL)
			exit_error("[Info] Client disconnected.");
		split = ft_strsplit(command, ' ');
		process_command(handler, split[0], &(split[1]));
		ft_strarr_del(&split);
		ft_strdel(&command);
	}
}

/*
** Non-blocking server loop
*/

static void	server_running(t_server_handler *handler, int port)
{
	pid_t				pid;

	printf("[Info] ft_p server running on port %d\n", port);
	while (42)
	{
		handler->pi.cs = create_cs(handler->pi.socket);
		pid = fork();
		if (pid > 0)
			close(handler->pi.cs);
		else if (pid == 0)
		{
			write(handler->pi.cs, REP_SERVICE_READY, 33);
			wait_for_commands(handler);
		}
	}
}

void		server_listen(int port)
{
	t_server_handler	*handler;

	handler = init_server_handler();
	handler->pi.port = port;
	handler->dtp.port = port - 1;
	handler->pi.socket = create_srv_socket(port);
	handler->dtp.socket = create_srv_socket(handler->dtp.port);
	if ((listen(handler->dtp.socket, BACKLOG) == -1))
		exit_error("[Fatal error] Error establishing data connection socket.");
	if ((listen(handler->pi.socket, BACKLOG) == -1))
		exit_error("[Fatal error] Error establishing control connection \
		socket.");
	server_running(handler, port);
}
