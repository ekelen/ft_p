/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:46:07 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:46:07 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

void	usage(void)
{
	ft_putendl_fd("server usage: ./server <port>", 2);
}

int		main(int ac, char **av)
{
	int	port;

	if (ac != 2)
	{
		usage();
		return (1);
	}
	port = ft_atoi(av[1]);
	server_listen(port);
}
