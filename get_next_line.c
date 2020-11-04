/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 13:14:26 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/25 17:27:46 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	free_all(char *storage, char *buf, char *line)
{
	free(buf);
	free(storage);
	free(line);
	return (-1);
}

int	success_gnl(char *nl_p, char **storage, char *buf, char **line)
{
	char *tmp;

	tmp = NULL;
	*nl_p = '\0';
	if (!(*line = ft_strjoin(*storage, buf)))
		return (free_all(*storage, buf, *line));
	tmp = *storage;
	if (!(*storage = ft_strjoin((nl_p + 1), NULL)))
		return (free_all(tmp, buf, *line));
	safe_free(&tmp);
	safe_free(&buf);
	return (1);
}

int	finish_gnl(char **storage, char *buf, char **line)
{
	if (!(*line = ft_strjoin(*storage, buf)))
		return (free_all(*storage, buf, *line));
	safe_free(storage);
	safe_free(&buf);
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
			return (free_all(*storage, buf, *line));
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
			return (free_all(*storage, buf, *line));
		safe_free(storage);
		*storage = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	static char	*storage;
	char		*buf;
	char		*tmp;

	buf = NULL;
	if (!line || fd < 0 || BUFFER_SIZE <= 0)
		return (free_all(storage, buf, NULL));
	*line = NULL;
	if (storage && (tmp = get_newline(storage, ft_strlen(storage))))
		return (success_gnl(tmp, &storage, buf, line));
	if (!(buf = malloc(BUFFER_SIZE + 1)))
		return (free_all(storage, buf, *line));
	return (loop_gnl(fd, &storage, buf, line));
}
