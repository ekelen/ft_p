/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:08 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:08 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

/*
** Catch and destroy zombie <pid>
** Return -1 for nonzero exit status of <pid>, else 0
*/

static int	wait_exec(pid_t pid)
{
	int				status;
	struct rusage	m_rusage;

	wait4(pid, &status, 0, &m_rusage);
	if (WEXITSTATUS(status))
		return (-1);
	return (0);
}

int			exec_builtin_local(char *bin, char **av)
{
	pid_t			pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		if (execv(bin, av) < 0)
			return (int_error("Error when executing local command."));
	}
	else
	{
		if (wait_exec(pid) == -1)
			return (-1);
		return (0);
	}
	return (0);
}
