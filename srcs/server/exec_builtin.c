/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:45:22 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:45:22 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ftp_server.h"

int	exec_builtin(t_server_handler *handler, char *bin, char **args)
{
	int				status;
	struct rusage	m_rusage;
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		return (int_error("fork error"));
	if (pid == 0)
	{
		dup2(handler->dtp.cs, 1);
		if (execv(bin, args) < 0)
			return ((int_error("execv error")));
	}
	else
	{
		wait4(pid, &status, 0, &m_rusage);
		if (WEXITSTATUS(status))
			return (int_error("wait4 error"));
	}
	return (0);
}
