/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 18:45:49 by tgerman           #+#    #+#             */
/*   Updated: 2026/10/22 18:45:49 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (len);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strjoin(char *stash, const char *buf)
{
	size_t	stash_len;
	size_t	buf_len;
	size_t	i;
	char	*new_stash;

	stash_len = ft_strlen(stash);
	buf_len = ft_strlen(buf);
	new_stash = malloc(stash_len + buf_len + 1);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (i < stash_len + buf_len)
	{
		if (i < stash_len)
			new_stash[i] = stash[i];
		else
			new_stash[i] = buf[i - stash_len];
		i++;
	}
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}

char	*ft_strchr(const char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strldup(const char *s, size_t len)
{
	size_t	i;
	char	*new_str;

	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
