/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylamsiah <ylamsiah@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:04:12 by ylamsiah          #+#    #+#             */
/*   Updated: 2023/08/16 17:46:39 by ylamsiah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	int		i;
	char	*buffer;
	char	s;
	int		count;

	if (fd < 0 || !BUFFER_SIZE)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * 100000);
	if (!buffer)
		return (NULL);
	count = read(fd, &s, 1);
	i = 0;
	while (count > 0)
	{
		buffer[i++] = s;
		if (s == '\n')
			break ;
		count = read(fd, &s, 1);
	}
	buffer[i] = '\0';
	if (!i || count < 0)
		return (free(buffer), NULL);
	return (buffer);
}
