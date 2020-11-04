/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:00:33 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/25 18:53:55 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	free_all(char **storage, char *buf, char *line)
{
	int i;

	i = 0;
	while (i < FD_MAX)
		free(storage[i++]);
	free(buf);
	free(line);
	return (-1);
}

int	success_gnl(char *nl_p, char **storage, char *buf, char **line)
{
	char *tmp;

	tmp = NULL;
	*nl_p = '\0';
	if (!(*line = ft_strjoin(*storage, buf)))
		return (-1);
	tmp = *storage;
	if (!(*storage = ft_strjoin((nl_p + 1), NULL)))
	{
		safe_free(&tmp);
		return (-1);
	}
	safe_free(&tmp);
	safe_free(&buf);
	return (1);
}

int	finish_gnl(char **storage, char *buf, char **line)
{
	if (!(*line = ft_strjoin(*storage, buf)))
		return (-1);
	return (0);
}

int	loop_gnl(int fd, char **storage, char *buf, char **line)
{
	char		*tmp;
	ssize_t		read_len;

	while (1)
	{
		read_len = read(fd, buf, BUFFER_SIZE);
		if (read_len < 0)
			return (-1);
		buf[read_len] = '\0';
		if (read_len < BUFFER_SIZE)
		{
			if ((tmp = get_newline(buf, read_len)))
				return (success_gnl(tmp, storage, buf, line));
			else
				return (finish_gnl(storage, buf, line));
		}
		if ((tmp = get_newline(buf, BUFFER_SIZE)))
			return (success_gnl(tmp, storage, buf, line));
		if (!(tmp = ft_strjoin(*storage, buf)))
			return (-1);
		safe_free(storage);
		*storage = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	static char *storage[FD_MAX];
	char		*buf;
	char		*tmp;
	int			res;

	buf = NULL;
	if (!line || fd < 0 || FD_MAX <= fd || BUFFER_SIZE <= 0)
		return (free_all(storage, buf, NULL));
	*line = NULL;
	if (storage[fd] && (tmp = get_newline(storage[fd], ft_strlen(storage[fd]))))
	{
		if ((res = success_gnl(tmp, &storage[fd], buf, line)) < 0)
			return (free_all(storage, buf, *line));
		else
			return (res);
	}
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (free_all(storage, buf, *line));
	if ((res = loop_gnl(fd, &storage[fd], buf, line)) < 0)
		return (free_all(storage, buf, *line));
	else if (res == 0)
		return (finish_free(&storage[fd], buf));
	else
		return (res);
}
