# hexdump

Reimplementation of Unix `hexdump` program.

Got tired of the different `hd` and `hexdump` versions around and their flags, and various packages they are included in with different defaults depending on system distribution.

## Use

```
$ make clean && make && ./hexdump hexdump.c | head
00000000  23 69 6e 63 6c 75 64 65  20 3c 73 74 64 69 6f 2e  |#include <stdio.|
00000010  68 3e 0a 23 69 6e 63 6c  75 64 65 20 3c 73 74 64  |h>.#include <std|
00000020  6c 69 62 2e 68 3e 0a 0a  23 64 65 66 69 6e 65 20  |lib.h>..#define |
00000030  4d 41 58 5f 42 55 46 5f  53 49 5a 20 28 32 20 2a  |MAX_BUF_SIZ (2 *|
00000040  20 31 30 32 34 20 2a 20  31 30 32 34 29 0a 23 64  | 1024 * 1024).#d|
00000050  65 66 69 6e 65 20 4d 49  4e 5f 42 55 46 5f 53 49  |efine MIN_BUF_SI|
00000060  5a 20 28 32 20 2a 20 31  30 32 34 29 0a 0a 73 74  |Z (2 * 1024)..st|
00000070  61 74 69 63 20 63 68 61  72 20 73 61 66 65 5f 63  |atic char safe_c|
00000080  68 61 72 28 63 68 61 72  20 63 29 20 7b 0a 20 20  |har(char c) {.  |
00000090  69 66 20 28 63 20 3d 3d  20 27 5c 6e 27 29 20 7b  |if (c == '\n') {|
```
