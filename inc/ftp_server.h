/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_server.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:27:55 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:29:44 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_SERVER_H
# define FTP_SERVER_H

# define BACKLOG 42
# define BUF_SIZE 1024
# define AUTH_REQUIRED true

/*
** REPLIES
*/

# define REP_DTP_OPEN "125 Data connection already open; transfer starting.\r\n"
# define REP_OPEN_DTP "150 File status okay; about to open data connection.\r\n"

# define REP_OK "200 Command okay.\r\n"
# define REP_SERVICE_READY "220 Service ready for new user.\r\n"
# define REP_CLOSING_CS_PI "221 Closing. Logged out if appropriate.\r\n"
# define REP_CLOSING_DTP "226 Closing data connection.\r\n"
# define REP_ENTER_PASV "227 Entering Passive Mode\r\n"
# define REP_PASV "227 Passive Mode ("
# define REP_LOGIN_SUCCESS "230 User logged in, proceed.\r\n"
# define REP_FILE_ACT_OK "250 Requested file action okay, completed.\r\n"

# define REP_EXPECT_PASS "331 User name okay, need password.\r\n"

# define REP_NOT_AVAILABLE "421 Not available, Closing.\r\n"
# define REP_FILE_ISSUE "450 Requested file action not taken.\r\n"

# define REP_CANNOT_CLOSE_CS_PI "500 Unable to close client socket...\r\n"
# define REP_LIST_ERR "500 List Error.\r\n"
# define REP_ACTIVE_ERR "500 Active mode not supported.\r\n"
# define REP_SYNTAX_ERR "500 Syntax error, command unrecognized.\r\n"
# define REP_SYNTAX_ERR_ARGS "501 Syntax error in parameters or arguments.\r\n"
# define REP_UNIMPLEMENTED_CMD "502 Command not implemented.\r\n"
# define REP_USERNAME_MISSING "503 No user found.\r\n"
# define REP_ARGS_ISSUE "504 Command not implemented for that parameter.\r\n"
# define REP_ACTION_NOT_TAKEN "550 Action not taken. File unavailable.\r\n"
# define REP_AUTH_ERROR "530 Not logged in.\r\n"

# define SERVER_FS_ROOT "ftproot"

# include "ft_p.h"

typedef struct					s_connection
{
	int		port;
	char	address[15];
	int		socket;
	int		cs;
}								t_connection;

typedef enum					e_mode
{
	ACTIVE,
	PASSIVE
}								t_mode;

typedef struct					s_server_handler
{
	t_connection		pi;
	t_connection		dtp;
	t_mode				mode;
	struct sockaddr_in	sin_dtp;
	char				*root;
	char				*username;
	bool				logged;
	char				data_type_code;
}								t_server_handler;

typedef struct					s_command_handler
{
	char	*command_name;
	void	(*fn)(t_server_handler *, char **);
	bool	auth_required;
}								t_command_handler;

typedef struct					s_user_pass
{
	char	*username;
	char	*password;
}								t_user_pass;

typedef void					(*t_builtin)(t_server_handler *, char **);

void							server_listen(int port);
void							send_reply(t_server_handler *handler,
									char *reply);
void							process_command(t_server_handler *handler,
									char *command_name, char **args);
int								create_cs(int socket);
int								create_srv_socket(int port);
int								exec_builtin(t_server_handler *handler,
									char *bin, char **args);
char							*get_path(t_server_handler *handler,
									char *input);
t_server_handler				*init_server_handler();
void							free_handler(t_server_handler *h);
bool							command_needs_auth(char *command_name, int i);
bool							check_src_file_path(t_server_handler *handler,
									char *filepath);
bool							check_dst_file_path(t_server_handler *handler,
									char *filepath);
bool							check_path(t_server_handler *handler,
									char *path);
void							handle_user(t_server_handler *handler,
									char **args);
void							handle_pass(t_server_handler *handler,
									char **args);
void							handle_quit(t_server_handler *handler,
									char **args);
void							handle_passive(t_server_handler *handler,
									char **args);
void							handle_port(t_server_handler *handler,
									char **args);
void							handle_list(t_server_handler *handler,
									char **args);
void							handle_stor(t_server_handler *handler,
									char **args);
void							handle_retr(t_server_handler *handler,
									char **args);
void							handle_type(t_server_handler *handler,
									char **args);
void							handle_pwd(t_server_handler *handler,
									char **args);
void							handle_cwd(t_server_handler *handler,
									char **args);
void							handle_list(t_server_handler *handler,
									char **args);

static t_command_handler		g_command_handler_list[] =
{
	{ "QUIT", handle_quit, false },
	{ "USER", handle_user, false },
	{ "PASS", handle_pass, false },
	{ "PASV", handle_passive, AUTH_REQUIRED },
	{ "PORT", handle_port, AUTH_REQUIRED },
	{ "PWD", handle_pwd, AUTH_REQUIRED },
	{ "STOR", handle_stor, AUTH_REQUIRED },
	{ "RETR", handle_retr, AUTH_REQUIRED },
	{ "CWD", handle_cwd, AUTH_REQUIRED },
	{ "TYPE", handle_type, AUTH_REQUIRED },
	{ "LIST", handle_list, AUTH_REQUIRED },
	{ NULL, NULL, NULL }
};

static t_user_pass				g_user_pass_list[] = {
	{ "user42", "pass42" },
	{ "user21", "pass21" },
	{ NULL, NULL }
};

#endif
