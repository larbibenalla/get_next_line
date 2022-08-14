/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labenall <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 14:23:42 by labenall          #+#    #+#             */
/*   Updated: 2022/08/14 14:23:46 by labenall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// join and free
char	*ft_free(char *buff, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buff, buf);
	free(buff);
	return (temp);
}

// delete line find
char	*ft_next(char *buff)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	// find len of first line
	while (buff[i] && buff[i] != '\n')
		i++;
	// if eol == \0 return NULL
	if (!buff[i])
	{
		free(buff);
		return (NULL);
	}
	// len of file - len of firstline + 1
	line = ft_calloc((ft_strlen(buff) - i + 1), sizeof(char));
	i++;
	j = 0;
	// line == buff
	while (buff[i])
		line[j++] = buff[i++];
	free(buff);
	return (line);
}

// take line for return
char	*ft_line(char *buff)
{
	char	*line;
	int		i;

	i = 0;
	// if no line return NULL
	if (!buff[i])
		return (NULL);
	// go to the eol
	while (buff[i] && buff[i] != '\n')
		i++;
	// malloc to eol
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	// line = buff
	while (buff[i] && buff[i] != '\n')
	{
		line[i] = buff[i];
		i++;
	}
	// if eol is \0 or \n, replace eol by \n
	if (buff[i] && buff[i] == '\n')
		line[i++] = '\n';
	return (line);
}

char	*read_file(int fd, char *res)
{
	char	*buff;
	int		byte_read;

	// malloc if res dont exist
	if (!res)
		res = ft_calloc(1, 1);
	// malloc buff
	buff = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	byte_read = 1;
	while (byte_read > 0)
	{
		// while not eof read
		byte_read = read(fd, buff, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buff);
			return (NULL);
		}
		// 0 to end for leak
		buff[byte_read] = 0;
		// join and free
		res = ft_free(res, buff);
		// quit if \n find
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;

	// error handling
	if (fd < 0 || BUFFER_SIZE <= 0 /*|| read(fd, 0, 0) < 0*/)
		return (NULL);
	buff = read_file(fd, buff);
	if (!buff)
		return (NULL);
	line = ft_line(buff);
	buff = ft_next(buff);
	return (line);
}
