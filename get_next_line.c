/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerman <tgerman@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-10-22 09:49:34 by tgerman           #+#    #+#             */
/*   Updated: 2026-10-22 09:49:34 by tgerman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_from_stash(char *stash)
{
	char	*end;

	end = ft_strchr(stash, '\n');
	if (end)
		return (ft_strldup(stash, end + 1 - stash));
	return (ft_strldup(stash, ft_strlen(stash)));
}

void	*ft_free_and_null(char **stash)
{
	free(*stash);
	*stash = NULL;
	return (NULL);
}

char	*ft_read_to_stash(int fd, char *stash)
{
	char		*buf;
	ssize_t		readen_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= LONG_MAX)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	readen_bytes = 1;
	while (readen_bytes > 0 && !ft_strchr(stash, '\n'))
	{
		readen_bytes = read(fd, buf, BUFFER_SIZE);
		if (readen_bytes == -1)
		{
			free(buf);
			return (ft_free_and_null(&stash));
		}
		buf[readen_bytes] = '\0';
		if (readen_bytes > 0)
			stash = ft_strjoin(stash, buf);
		if (!stash)
			readen_bytes = -1;
	}
	free(buf);
	return (stash);
}

char	*ft_move_stash(char *stash)
{
	char	*new_stash_start;
	char	*new_stash;

	new_stash_start = ft_strchr(stash, '\n');
	if (!new_stash_start || !new_stash_start[1])
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_strldup(new_stash_start + 1, ft_strlen(new_stash_start + 1));
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*new_line;

	stash = ft_read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	new_line = ft_get_from_stash(stash);
	if (!new_line)
		return (ft_free_and_null(&stash));
	stash = ft_move_stash(stash);
	return (new_line);
}
