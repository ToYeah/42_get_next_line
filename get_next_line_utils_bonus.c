/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:00:03 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/25 01:29:49 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_newline(const char *s, size_t len)
{
	size_t i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] != '\n')
	{
		if (!(i < len))
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	len;

	len = 1;
	i = 0;
	if (s1)
		while (s1[i++])
			len++;
	i = 0;
	if (s2)
		while (s2[i++])
			len++;
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			res[i++] = *s1++;
	if (s2)
		while (*s2)
			res[i++] = *s2++;
	res[i] = '\0';
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

void	safe_free(char **target)
{
	free(*target);
	*target = NULL;
}

int		finish_free(char **storage, char *buf)
{
	safe_free(storage);
	safe_free(&buf);
	return (0);
}
