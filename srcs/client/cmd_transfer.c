/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_transfer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:41:17 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:42:01 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

/*
** i + 1 == 0
** hacky way to check for unsigned type limit
*/

static char	*filename_from_path(char *s, unsigned int i)
{
	if (i == 0 || i + 1 == 0)
		return (s);
	if (s[i] == '/')
		return (s + i + 1);
	return (filename_from_path(s, i - 1));
}

int			handle_get(t_client_handler *handler, char **args)
{
	unsigned int	strcount;

	strcount = ft_count_strs(args);
	if (strcount < 1 || strcount > 2)
	{
		ft_putendl_fd("ERROR: Usage: get <source \
		file path> <new file name>", 2);
		return (ERR_FMT);
	}
	handler->src_pathname = args[0];
	handler->dst_pathname = strcount == 1 ?
		filename_from_path(args[0], ft_strlen(args[0]) - 2) :
		args[1];
	if (handler->dtp.socket == -1 && handle_passive(handler, NULL) == 0)
		get_reply(handler);
	send_command(handler, "RETR ", handler->src_pathname);
	handler->dtp_action = handle_on_ok_to_get;
	return (0);
}

int			handle_put(t_client_handler *handler, char **args)
{
	unsigned int	strcount;

	strcount = ft_count_strs(args);
	if (strcount < 1 || strcount > 2)
	{
		ft_putendl_fd("ERROR: Usage: put <source file path> \
		<new file name>", 2);
		return (ERR_FMT);
	}
	handler->src_pathname = args[0];
	handler->dst_pathname = strcount == 1 ?
		filename_from_path(args[0], ft_strlen(args[0]) - 2) :
		args[1];
	if (!file_ok(handler->src_pathname))
		return (int_error("ERROR: File: File unavailable."));
	if (handler->dtp.socket == -1 && handle_passive(handler, NULL) == 0)
		get_reply(handler);
	send_command(handler, "STOR", handler->dst_pathname);
	handler->dtp_action = handle_on_ok_to_put;
	return (0);
}
