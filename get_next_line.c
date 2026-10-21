
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
char *ft_strjoin(char *stash, const char *buf)
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
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}
char *ft_strldup(const char *s, size_t len)
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

char	*ft_get_from_stash(char **stash)
{
	char	*new_str;
	char	*end;
	char	*new_stash;
	size_t	stash_len;
	if (!(*stash))
		return (NULL);
	if (!(end = ft_strchr(*stash, '\n')))
		return (NULL);
	new_str = ft_strldup(*stash, end - *stash);
	stash_len = ft_strlen(*stash);
	new_stash = ft_strldup(*end, stash_len );
	free(*stash);
	*stash = new_stash;
	return (new_str);
}

char	*ft_get_next_line(int fd)
{

	ssize_t		readen_bytes;
	static char	*stash;
	char		*new_line;
	char		*buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= LONG_MAX)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	if ((new_line = ft_get_from_stash(&stash)))
		return (new_line);
	readen_bytes = 1;
	while (readen_bytes > 0 && ft_strchr(stash, '\n') == -1)
	{
		readen_bytes = read(fd,buf, BUFFER_SIZE);
		buf[BUFFER_SIZE] = '\0';
		if (readen_bytes > 0)
			ft_strjoin(stash, buf);
	}
	new_line = ft_get_from_stash(&stash);
	free(buf);
	return (new_line);
}


#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd = open("test.txt", O_RDONLY);
    char *line;

    while ((line = ft_get_next_line(fd)) != NULL)
    {
        printf("[%s]", line);
        free(line);
    }
    close(fd);
    return (0);
}
