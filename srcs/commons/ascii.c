/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekelen <ekelen@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 14:44:03 by ekelen            #+#    #+#             */
/*   Updated: 2019/10/20 14:44:42 by ekelen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/ft_p.h"

/*
** Update ASCII file content, replacing EOL in place
*/

char		*nvt_to_unix(char *file_content)
{
	int i;

	i = 0;
	while (file_content[i])
	{
		if (file_content[i] == '\n' && i > 0 && file_content[i - 1] == '\r')
		{
			file_content[i - 1] = '\n';
			file_content[i] = '\0';
			if (file_content[i + 1])
			{
				file_content = ft_strcat(file_content, file_content + i + 1);
				i--;
			}
		}
		i++;
	}
	return (file_content);
}

/*
** Allocate space, copy char content while replacing EOL UNIX->NVT
*/

char		*unix_to_nvt(char *file_content)
{
	int		i;
	int		j;
	char	*nvt_content;

	if ((nvt_content = malloc((ft_strlen(file_content) + 1) * 2)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (file_content[i])
	{
		nvt_content[j] = file_content[i];
		if (file_content[i] == '\n')
		{
			nvt_content[j] = '\r';
			j++;
			nvt_content[j] = '\n';
		}
		i++;
		j++;
	}
	nvt_content[j] = '\0';
	return (nvt_content);
}
