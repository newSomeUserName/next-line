



#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *stash, const char *buf);
char	*ft_strchr(const char *s, char c);
char	*ft_strldup(const char *s, size_t len);

#endif
