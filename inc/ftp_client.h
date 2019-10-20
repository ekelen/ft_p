/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftp_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:29:25 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:29:26 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTP_CLIENT_H
# define FTP_CLIENT_H

# include "ft_p.h"

# define RED "\033[31m"
# define GREEN "\033[32m"
# define BOLD "\033[1m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

# define USAGE "Usage: ./client <server_addr> <port>\n\n"
# define REP_NOT_AVAILABLE "421 Not available, Closing.\r\n"

# define ERR_FMT 3
# define ERR_NOT_IMPL 4

# define OK true
# define ERR false

# define OK_INT 0
# define ERR_INT 1

# define CLI_PI_BUFSIZE 1024
# define CLI_DTP_BUFSIZE 1024

typedef struct			s_cli_connection
{
	int		port;
	int		socket;
	char	*addr;
}						t_cli_connection;

typedef struct			s_client_handler
{
	t_cli_connection	pi;
	t_cli_connection	dtp;
	char				*root;
	char				data_type_code;
	char				*dst_pathname;
	char				*src_pathname;
	char				current_command[5];
	int					(*dtp_action)(struct s_client_handler *);
}						t_client_handler;

typedef int	(*t_on_cli_command)(t_client_handler *, char **);

typedef struct			s_cli_cmd
{
	char				*command_name;
	char				*input_command;
	t_on_cli_command	fn;
}						t_cli_cmd;

int						handle_pwd(t_client_handler *handler, char **args);
int						handle_user(t_client_handler *handler, char **args);
int						handle_password(t_client_handler *handler, char **args);
int						handle_passive(t_client_handler *handler, char **args);
int						handle_cd(t_client_handler *handler, char **args);
int						handle_get(t_client_handler *handler, char **args);
int						handle_put(t_client_handler *handler, char **args);
int						handle_quit(t_client_handler *handler, char **args);
int						handle_ls(t_client_handler *handler, char **args);
int						handle_type(t_client_handler *handler, char **args);

static t_cli_cmd		g_cli_cmd_list[] =
{
	{ "PWD", "pwd", handle_pwd },
	{ "USER", "user", handle_user },
	{ "PASS", "password", handle_password },
	{ "PASS", "pass", handle_password },
	{ "PASV", "passive", handle_passive },
	{ "CWD", "cd", handle_cd },
	{ "RETR", "get", handle_get },
	{ "STOR", "put", handle_put },
	{ "QUIT", "quit", handle_quit },
	{ "LIST", "ls", handle_ls },
	{ "TYPE", "type", handle_type },
	{ NULL, NULL, NULL },
};

typedef struct			s_reply_display
{
	char	*color;
	char	*text;
}						t_reply_display;

static t_reply_display	g_display_replies[] =
{
	{ "", "" },
	{ BLUE, "INTERMEDIATE ACTION: " },
	{ GREEN, "SUCCESS: " },
	{ MAGENTA, "PENDING: " },
	{ CYAN, "ABORT: " },
	{ RED, "FAILURE: " }
};

typedef int				(*t_action)(t_client_handler *, char *);

typedef struct			s_reply_action
{
	unsigned int	code;
	int				(*action)(struct s_client_handler *, char *msg);
}						t_reply_action;

/*
** client_dtp.c
*/

int						handle_on_ok_to_get(t_client_handler *h);
int						handle_on_ok_to_put(t_client_handler *h);
int						handle_on_ok_to_ls(t_client_handler *h);
int						handle_dtp_action(t_client_handler *h, char *msg);
int						close_dtp(t_client_handler *h, char *msg);
bool					open_dtp(t_client_handler *h,\
							char reply[CLI_PI_BUFSIZE]);
bool					create_client_dtp(t_client_handler *h, char *reply);

/*
** client_handler.c
*/

t_client_handler		*init_cli_handler();
int						handle_close_action(t_client_handler *h, char *msg);
void					free_cli_handler(t_client_handler *handler);

/*
** client_parse_reply.c
*/

int						handle_on_agree_dtp(t_client_handler *h, char *msg);
int						handle_on_quit(t_client_handler *h, char *msg);

static t_reply_action	g_reply_actions[] =
{
	{ 227, handle_on_agree_dtp },
	{ 221, handle_on_quit },
	{ 125, handle_dtp_action },
	{ 150, handle_dtp_action },
	{ 421, handle_close_action },
	{ 550, close_dtp },
	{ 0, NULL }
};

/*
** client_interface.c
*/

void					put_client_connect_confirm(char *addr, int port);
void					ft_putstr_in_brackets(char *s, int fd);
void					ftp_display_prompt(void);
void					display_reply(unsigned int code, char *msg);

/*
** client_pi.c
*/

bool					parse_connect_string(t_client_handler *h, char *av[]);
bool					create_client_pi(t_client_handler *h, char *av[]);
bool					on_connect_pi(t_client_handler *h);

/*
** parse_cli_cmd.c
*/

t_on_cli_command		*get_cmd_handler(t_client_handler *h,\
						char *input_cmd, unsigned int i);

/*
** replies.c
*/

void					get_reply(t_client_handler *h);

/*
** reply_actions.c
*/

t_action				*get_action(unsigned int reply_code, unsigned int i);

/*
** send_command.c
*/

void					send_command(t_client_handler *handler,\
						char *name, char *arg);

#endif
