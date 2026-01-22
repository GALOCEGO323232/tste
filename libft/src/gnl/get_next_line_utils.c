/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 23:32:00 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/08 23:32:00 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_join_and_free(char *s1, char *s2, size_t len1, size_t len2);

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	return (gnl_join_and_free(s1, s2, len1, len2));
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*gnl_free(void *ptr1, void *ptr2)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	return (NULL);
}

static char	*gnl_join_and_free(char *s1, char *s2, size_t len1, size_t len2)
{
	char	*res;
	size_t	i;

	res = malloc(len1 + len2 + 1);
	if (!res)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (++i < len1)
		res[i] = s1[i];
	i = -1;
	while (++i < len2)
		res[len1 + i] = s2[i];
	res[len1 + len2] = '\0';
	free(s1);
	return (res);
}
