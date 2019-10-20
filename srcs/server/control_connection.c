/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_connection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:17 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:18 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static bool	check_username(char *username, int i)
{
	if (g_user_pass_list[i].username == NULL)
		return (false);
	if (ft_strcmp(g_user_pass_list[i].username, username) == 0)
		return (true);
	return (check_username(username, i + 1));
}

static bool	check_password(char *username, char *password, int i)
{
	if (g_user_pass_list[i].username == NULL)
		return (false);
	if (ft_strcmp(g_user_pass_list[i].username, username) == 0)
	{
		if (ft_strcmp(password, g_user_pass_list[i].password) == 0)
			return (true);
	}
	return (check_password(username, password, i + 1));
}

bool		command_needs_auth(char *command_name, int i)
{
	if (g_command_handler_list[i].command_name == NULL)
		return (false);
	if (ft_strcmp(command_name, g_command_handler_list[i].command_name) == 0)
		return (g_command_handler_list[i].auth_required);
	return (command_needs_auth(command_name, i + 1));
}

void		handle_pass(t_server_handler *handler, char **args)
{
	char	*password;

	password = args[0];
	if (handler->username == NULL)
		send_reply(handler, REP_USERNAME_MISSING);
	else if (check_password(handler->username, password, 0))
	{
		handler->logged = true;
		ft_putendl("[Info] Client authenticated.");
		send_reply(handler, REP_LOGIN_SUCCESS);
	}
	else
		send_reply(handler, REP_AUTH_ERROR);
}

void		handle_user(t_server_handler *handler, char **args)
{
	char	*username;

	username = args[0];
	handler->logged = false;
	if (!check_username(username, 0))
	{
		send_reply(handler, REP_AUTH_ERROR);
		return ;
	}
	if (handler->username != NULL &&
		ft_strcmp(handler->username, username) == 0 && handler->logged)
	{
		send_reply(handler, REP_LOGIN_SUCCESS);
		return ;
	}
	if (handler->username)
		ft_strdel(&(handler->username));
	handler->username = ft_strdup(username);
	send_reply(handler, REP_EXPECT_PASS);
}
