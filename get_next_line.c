
#include "get_next_line.h"


size_t	ft_get_newline(const char *s)
{
	size_t	end;

	end = 0;
	while (s[end])
	{
		if (s[end] == '\n')
			return (end);
		end++;
	}
	return (0);
}

size_t ft_strlen(const char *s)
{
	size_t	len;
	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_add(const char *dest, char *old_buf)
{

}

#include <stdlib.h>
char *ft_join(const char *buf, const char *stash)
{
	char	*new_stash;
	size_t	start;
	size_t	end;
	if (stash == NULL)
	{
		stash = buf;
		return (stash);
	}
	new_stash = malloc(ft_strlen(buf) + ft_strlen(stash) + 1);
	start = 0;
	while (start < ft_strlen(stash))
		new_stash[start++] = stash[start];
	end = start;
	while (start < ft_strlen(buf) + ft_strlen(stash))
	{
		new_stash[start] =
	}

}

char	*get_next_line(int fd)
{

	ssize_t	readen_bytes;
	size_t	end;
	static char *stash;
	static char *buf;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	readen_bytes = read(fd,buf,BUFFER_SIZE);
	while (!(readen_bytes == 0 || readen_bytes == -1))
	{
		if (!(end = ft_get_newline(buf)))

		readen_bytes = read(fd,buf,BUFFER_SIZE);


	}


	return (NULL);
}
