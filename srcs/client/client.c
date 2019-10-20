/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:39:52 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:39:52 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

static void	sigint_handler(int i)
{
	(void)i;
	ft_putchar('\n');
	ftp_display_prompt();
}

int			main(int ac, char *av[])
{
	t_client_handler	*handler;
	bool				ok;

	if (ac < 3)
	{
		ft_putstr_fd(USAGE, 2);
		return (1);
	}
	signal(SIGINT, &sigint_handler);
	if ((handler = init_cli_handler()) == NULL)
		return (ERR_INT);
	if (!(parse_connect_string(handler, av)))
		return (ERR_INT);
	if (!(create_client_pi(handler, av)))
		return (ERR_INT);
	ok = on_connect_pi(handler);
	free_cli_handler(handler);
	return (ok ? 0 : 1);
}
