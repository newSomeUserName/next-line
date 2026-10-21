
#include "get_next_line.h"


size_t	ft_get_line(const char *s)
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


#include <stdlib.h>

char *strdup(const char *s)
{
	size_t len;
	size_t i;
	char *str;


	i = 0;
	len = ft_strlen(s);
	str = malloc(len + 1);
	if (!str)
		return (NULL);	
	while (i < len)
		str[i++] = s[i];
	str[i] = '\0';
	write(1,str, len);
	return (str);	
}

char *ft_join(char *stash, char *buf)
{
	char *new_s;
	char *start;
	size_t len;

	len = ft_strlen(stash) + ft_strlen(buf);
	new_s = malloc(len  + 1);
	new_s = '\0';
	while (*stash)
	{
		*new_s = *stash;
		new_s++;
		stash++; 
	}
	while (*buf)
	{
		*new_s = *buf;
		new_s++;
		buf++; 
	}
	return (start);
	
}
char *ft_create_stash(char *stash, char *buf)
{
	if (stash == NULL)
		return(strdup(buf));
	
	return (ft_join(stash, buf));
	
}

char	*get_next_line(int fd)
{

	ssize_t	readen_bytes;
	size_t	end;
	static char *stash;
	char *buf;
	char *start;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
			return (NULL);
	if (stash != NULL && (end = ft_get_line(stash)) != 0)
		write(1, stash, end);
	buf[BUFFER_SIZE] = '\0';
	start = buf;
	readen_bytes = read(fd,buf,BUFFER_SIZE);
	while (readen_bytes > 0)
	{
		
		while ((end = ft_get_line(buf)) != 0)
		{
			write(1, buf, end + 1);
			buf += end  + 1;
		}
		//BUF_SIZE=10 AAAAAA\nBBB
		if (*buf != buf[BUFFER_SIZE])
		{
			stash = ft_create_stash(stash, buf);
		}
		
		buf = start;
		readen_bytes = read(fd,buf,BUFFER_SIZE);
		write(1,buf, BUFFER_SIZE);
	}
	return (NULL);
}


#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    int   fd = open("test2.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        // printf("[%s]", line);
        // free(line);
    }
    close(fd);
    return (0);
}

// void	ft_add(const char *dest, char *old_buf)
// {

// }

// #include <stdlib.h>
// char *ft_join(const char *buf, char *stash)
// {
// 	char	*new_stash;
// 	size_t	start;
// 	size_t	end;
// 	if (stash == NULL)
// 	{
// 		stash = buf;
// 		return (stash);
// 	}
// 	new_stash = malloc(ft_strlen(buf) + ft_strlen(stash) + 1);
// 	start = 0;
// 	while (start < ft_strlen(stash))
// 		new_stash[start++] = stash[start];
// 	end = start;
// 	while (start < ft_strlen(buf) + ft_strlen(stash))
// 	{
// 		new_stash[start] = 
// 	}

// }