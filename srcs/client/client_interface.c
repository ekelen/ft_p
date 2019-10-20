/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:39:10 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:39:10 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

void			ftp_display_prompt(void)
{
	ft_putstr(BOLD);
	ft_putstr("ft_p » ");
	ft_putstr(RESET);
}

void			put_client_connect_confirm(char *addr, int port)
{
	printf("Connected to %s%s%s ", BOLD, addr, RESET);
	printf("on port %s%d%s\n", BOLD, port, RESET);
}

void			ft_putstr_in_brackets(char *s, int fd)
{
	ft_putstr_fd("[", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd("]", fd);
}

void			ft_putnbr_in_brackets(int n, int fd)
{
	ft_putstr_fd("[", fd);
	ft_putnbr_fd(n, fd);
	ft_putstr_fd("]", fd);
}

void			display_reply(unsigned int code, char *msg)
{
	unsigned int index;

	index = code / 100;
	ft_putstr(g_display_replies[index].color);
	ft_putstr(g_display_replies[index].text);
	ft_putstr(RESET);
	ft_putstr(msg);
	ft_putchar('\n');
}
