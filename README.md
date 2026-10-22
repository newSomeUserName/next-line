*This project has been created as part of the 42 curriculum by tgerman.*

# get_next_line

## Description

`get_next_line` is a C function that returns one line at a time from a file
descriptor:

```c
char	*get_next_line(int fd);
```

Each call returns the next line, including its terminating `\n`. The last
line has no `\n` if the file does not end with one. The function returns
`NULL` when there is nothing left to read or when an error occurs. It works
with regular files and with standard input.

The project teaches static variables, buffered reading with `read()`, and
careful dynamic memory management. Only `read`, `malloc` and `free` are
allowed.

### Bonus

The bonus version (`*_bonus.[ch]`) uses a single static variable and can read
from several file descriptors in turn (for example fd 3, then 4, then 3 again)
without mixing up their reading states.

## Instructions

Compile `get_next_line` together with your own `main`:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c
```

Bonus:

```sh
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c
```

`BUFFER_SIZE` is optional and defaults to `42`. The bonus also defines
`FD_MAX` (default `1024`), the highest supported file descriptor + 1. You can
override it with `-D FD_MAX=n`.

Example `main.c`:

```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
```

The caller must `free` every line it receives.

## Algorithm

### Idea

`read()` returns a fixed number of bytes (`BUFFER_SIZE`), and that chunk does
not line up with lines. A chunk may contain several lines, or only part of
one. The bytes that were read but not yet returned must survive until the next
call. A **static** pointer, the *stash*, keeps them between calls.

### Steps of one call

1. **Read into the stash** (`ft_read_to_stash`): while the stash has no `\n`,
   `read()` `BUFFER_SIZE` bytes into a temporary buffer and append them to the
   stash (`ft_strjoin`). The loop stops when a `\n` appears, at end of file
   (`read` returns `0`), or on error (`-1`). On error the stash is freed and
   `NULL` is returned.
2. **Extract the line** (`ft_get_from_stash`): copy the stash up to and
   including the first `\n`. If there is no `\n`, copy the whole stash, which
   happens for the last line.
3. **Keep the rest** (`ft_move_stash`): build a new stash from the bytes after
   the `\n` and free the old one. If nothing is left, the stash becomes `NULL`,
   so the next call starts from scratch and returns `NULL` at EOF.

### Why this approach

- **Reads as little as possible.** The function stops reading as soon as the
  stash contains a `\n`, as the subject requires, so it never loads the whole
  file. With a large `BUFFER_SIZE`, one `read` can cover many lines, and the
  later calls are served straight from the stash without reading again.
- **Works with any `BUFFER_SIZE`.** The same logic handles `1` (many reads per
  line) and `10000000` (one read for many lines). Only one temporary buffer
  is allocated, and it is freed before returning.
- **No leaks on any path.** Every allocation failure or read error frees the
  stash and sets it to `NULL` (`ft_free_and_null`). At EOF the stash is freed
  as well. Verified with `valgrind --leak-check=full`.
- **Bonus.** The single static variable becomes an array
  `static char *stash[FD_MAX]`, indexed by `fd`. Each descriptor keeps its own
  leftover bytes, so the descriptors do not interfere with each other. `fd` is
  checked against `0..FD_MAX-1` before indexing to avoid out-of-bounds access.

### Trade-off

Appending to the stash copies it on every `read` (`ft_strjoin`), so a very long
line with a tiny `BUFFER_SIZE` costs more copying. I accepted this for
simplicity and clarity, since typical lines are short.

## Resources

- `man 2 read`, `man 3 malloc`, `man 3 free`
- [Static variables in C (GeeksforGeeks)](https://www.geeksforgeeks.org/static-variables-in-c/)
- [File descriptors (Wikipedia)](https://en.wikipedia.org/wiki/File_descriptor)
- [Valgrind quick start](https://valgrind.org/docs/manual/quick-start.html)
- 42 Norm (norminette)

### AI usage

I wrote the mandatory implementation myself. I used an AI assistant (Claude)
for:

- **Testing:** checking the mandatory part with different `BUFFER_SIZE`
  values, edge-case files, stdin and invalid file descriptors, and running
  valgrind.
- **Norm:** fixing norminette formatting errors (tabs, blank lines,
  preprocessor indentation), with no logic changes.
- **Bonus:** adapting the mandatory code to the multi-fd version (the static
  array indexed by `fd` and the `fd` bounds check).
- **README:** drafting this file.

I reviewed and understand all of the code above.
