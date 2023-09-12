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

int ft_strlen(char *s)
{
	int i = 0;
	if (!s)
		return(0);
	while(*(s + i))
		i++;
	return(i);
}

char *ft_strdup(char *str)
{
	int i;
	char *s;

	s = (char *)malloc(ft_strlen(str) + 1 * sizeof(char));
	if (!s)
		return(NULL);
	i = 0;
	while(*(str + i))
	{
		*(s + i) = *(str + i);
		i++;
	}
	*(s + i) = '\0';
	return(s);
}

char *ft_strjoin(char *s1, char *s2)
{
	int len1 = ft_strlen(s1);
	int len2 = ft_strlen(s2);
	int i;

	char *s;
	s = (char *)malloc((len1 + len2 + 1) *sizeof(char)); 
	if (!s)
		return(NULL);
	i = 0;
	while(i < len1)
	{
		*(s + i) = *(s1 + i);
		i++;
	}
	i = 0;
	while(i < len2)
	{
		*(s + len1 + i) = *(s2 + i);
		i++;
	}
	*(s + len1 + i) = '\0';
	free((char *)s1);
	return(s);
}	

int size_line(char *s)
{
	int i;

	if (!s)
		return(-1);
	i = 0;
	while(*(s + i) && *(s + i) != '\n')
		i++;
	if (*(s + i) == '\0')
		return(-1);
	return(i);
}

char *read_line(char *s)
{
	char *new_l;
	int pos;
	int i;

	if (!s)
		return(NULL);
	pos = size_line(s);
	if (pos == -1)
		return(ft_strdup(s));
	new_l = (char *)malloc(pos + 2 *sizeof(char));
	if (!new_l)
		return(NULL);
	i = 0;
	while(*(s + i) != '\n')
	{
		*(new_l + i)= *(s + i);
		i++;
	}
	*(new_l + i)= '\n';
	*(new_l + i + 1) = '\0';
	return(new_l);
}

char *next_line(char *s)
{
	int pos;
	int len;
	char *next_l;
	
	if(!s)
		return(NULL);
	pos = size_line(s);
	len = ft_strlen(s);
	if (pos == -1 || (len - pos) == 1)
		return(free(s), NULL);
	next_l = ft_strdup(s + pos + 1);
	free((char *)s);
	return(next_l);
}

char *get_next_line(int fd)
{
	char *new_line;
	char *buffer;
	static char *static_l;
	int count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return(NULL);
	while(size_line(static_l) == -1)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
			break;
		*(buffer + count) = '\0';
		static_l = ft_strjoin(static_l, buffer);
	}
	free((char *)buffer);
	new_line = read_line(static_l);
	static_l = next_line(static_l);
	return(new_line);
}
