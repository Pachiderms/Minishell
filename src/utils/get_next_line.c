/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 16:24:46 by tzizi             #+#    #+#             */
/*   Updated: 2025/01/19 12:17:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_stash(char *_buffer)
{
	int		i;
	int		j;
	char	*next;

	i = 0;
	j = 0;
	while (_buffer[i] && _buffer[i] != '\n')
		i++;
	if (!_buffer[i])
	{
		free(_buffer);
		return (NULL);
	}
	next = ft_calloc(ft_strlen(_buffer) - i + 1, sizeof(char));
	if (!next)
		return (NULL);
	i++;
	while (_buffer[i + j])
	{
		next[j] = _buffer[i + j];
		j++;
	}
	free(_buffer);
	return (next);
}

char	*ft_free_gnl(char *_stash, char *_buffer)
{
	if (!_stash)
	{
		free(_buffer);
		return (NULL);
	}
	if (_stash[0] == 0)
	{
		free(_buffer);
		free(_stash);
		return (NULL);
	}
	else
	{
		free(_buffer);
		return (_stash);
	}
}

char	*ft_read(int _fd, char *_stash)
{
	int		readb;
	char	*buffer;

	readb = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	if (_stash == NULL)
		_stash = ft_calloc(1, sizeof(char));
	while (readb > 0)
	{
		readb = read(_fd, buffer, BUFFER_SIZE);
		if (readb <= 0)
			return (ft_free_gnl(_stash, buffer));
		buffer[readb] = '\0';
		_stash = ft_strjoin_free(_stash, buffer, 0);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (_stash);
}

char	*ft_line(char *_buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (_buffer[i] && _buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (_buffer[i] && _buffer[i] != '\n')
	{
		line[i] = _buffer[i];
		i++;
	}
	if (_buffer[i] && _buffer[i] == '\n')
		line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) == -1)
	{
		if (buffer[fd] != NULL)
		{
			free(buffer[fd]);
			buffer[fd] = NULL;
		}
		return (NULL);
	}
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_stash(buffer[fd]);
	return (line);
}
