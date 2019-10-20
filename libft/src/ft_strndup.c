/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:07:35 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:36:02 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*s;
	int		i;

	i = 0;
	if (!(s = (char *)malloc(n + 1)))
		return (NULL);
	while (s1[i] && n > 0)
	{
		s[i] = s1[i];
		i++;
		n--;
	}
	s[i] = '\0';
	return (s);
}
