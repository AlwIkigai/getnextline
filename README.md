# get_next_line

Read a file descriptor line-by-line in C.

This project implements `get_next_line(int fd)`, a function that returns the next line from a given file descriptor each time it is called. It maintains leftover buffered data between calls using static storage and builds lines using only low-level reads (`read`) and custom utility functions.

`get_next_line` was a key milestone in understanding buffered I/O, static state, and careful memory management in C.

---

## Overview

`get_next_line` reads from a file descriptor and returns one full line per call.

- If a newline (`\n`) exists, the returned line includes the newline.
- If EOF is reached without a trailing newline, the final line is still returned.
- Once no data remains, the function returns `NULL`.

This implementation uses a static buffer to preserve unread data between calls.

---

## Function Prototype

```c
char *get_next_line(int fd);
```

### Return Values

- Returns a heap-allocated string containing the next line
- Returns NULL on EOF when no data remains, or on error

## BUFFER_SIZE

The number of bytes read per system call is controlled by BUFFER_SIZE.
In this repository:
```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
```
You may override it at compile time:
```bash
cc -D BUFFER_SIZE=1000 ...
```
## Implementation Notes

- Uses a static buffer (warehouse) to persist data across function calls
- Reads chunks into a temporary buffer and appends them to the stored data
- Stops reading once a newline is found or EOF is reached

### Extracts a line:

- Copies up to and including \n if present
- Otherwise returns the remaining data as the final line
- Any leftover data after the newline is stored for the next call

### Build / Compile

Typical manual compilation:
```bash
cc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c
```
With a custom buffer size:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```
### Files

- get_next_line.c – core logic and buffered reading
- get_next_line_utils.c – string and memory helper functions
- get_next_line.h – function prototypes and macro definitions

## Notes

- Caller is responsible for freeing each returned line
- No forbidden libc functions are used
- Built according to 42 project constraints and coding standards

## Correctly handles:

- empty files
- files without trailing newline
- consecutive newlines
- invalid file descriptors
- small buffer sizes

## Author

Syed Ahmad
GitHub: https://github.com/AlwIkigai
