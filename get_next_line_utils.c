/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: totaisei <totaisei@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 17:34:43 by totaisei          #+#    #+#             */
/*   Updated: 2020/10/24 18:31:36 by totaisei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
