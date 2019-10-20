/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:16 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:16 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

void	exit_error(char const *message)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	exit(1);
}

int		int_error(char const *message)
{
	ft_putendl_fd(message, 2);
	return (-1);
}

bool	ft_puterr_ret(const char *msg)
{
	ft_putendl_fd(msg, 2);
	return (false);
}

void	*ft_puterr_null(const char *msg)
{
	ft_putendl_fd(msg, 2);
	return ((void*)NULL);
}
