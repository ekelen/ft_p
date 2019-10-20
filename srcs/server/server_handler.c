/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:47 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:48 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

static void			create_root_dir(t_server_handler *handler)
{
	char				**root;

	root = ft_strsplit("makedr -p -m 777 ftproot", ' ');
	if (exec_builtin_local("/bin/mkdir", root))
	{
		ft_strarr_del(&root);
		free_handler(handler);
		exit_error("Could not create ft_p root directory!");
	}
	ft_strarr_del(&root);
	if (ft_chdir(SERVER_FS_ROOT))
	{
		free_handler(handler);
		exit_error("Could not move to ft_p root directory.");
	}
	handler->root = NULL;
	if ((handler->root = getcwd(NULL, 0)) == NULL)
	{
		free_handler(handler);
		exit_error("Malloc error allocating for root dirname");
	}
}

t_server_handler	*init_server_handler(void)
{
	t_server_handler	*handler;

	handler = (t_server_handler *)malloc(sizeof(t_server_handler));
	if (handler == NULL)
		exit_error("Malloc error allocating memory for server_handler");
	create_root_dir(handler);
	ft_strcpy(handler->dtp.address, "127.0.0.1");
	handler->dtp.cs = -1;
	handler->logged = false;
	handler->username = NULL;
	handler->data_type_code = 'A';
	handler->mode = PASSIVE;
	return (handler);
}

void				free_handler(t_server_handler *handler)
{
	if (handler->username != NULL)
		ft_strdel(&(handler->username));
	free(handler);
}
