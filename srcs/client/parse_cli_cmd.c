/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cli_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:41:02 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:41:03 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_client.h"

static void			flush_cpy_client_cmd(t_client_handler *h, char *cmd)
{
	ft_bzero(h->current_command, 5);
	ft_strncpy(h->current_command, cmd, 4);
}

t_on_cli_command	*get_cmd_handler(t_client_handler *h,
	char *input_cmd, unsigned int i)
{
	if (g_cli_cmd_list[i].input_command == NULL || input_cmd == NULL)
	{
		ft_putstr_fd("ERROR: unknown command.\n", 2);
		return (NULL);
	}
	if (ft_strcmp(input_cmd, g_cli_cmd_list[i].command_name) == 0 \
		|| ft_strequ(input_cmd, g_cli_cmd_list[i].input_command))
	{
		flush_cpy_client_cmd(h, g_cli_cmd_list[i].command_name);
		return (&(g_cli_cmd_list[i].fn));
	}
	return (get_cmd_handler(h, input_cmd, i + 1));
}
