#include <stdio.h>
#include <stdlib.h>

#define MAX_BUF_SIZ (2 * 1024 * 1024)
#define MIN_BUF_SIZ (2 * 1024)

static char safe_char(char c) {
  if (c == '\n') {
    return '.';
  }

  if ((c > 32) && (c != 127) && (c != 255)) {
    return c;
  }

  return ' ';
}

static char * alloc_buffer(size_t * buf_siz) {
  char * buf;
  size_t try_buf_siz = MAX_BUF_SIZ;

  do {
    buf = malloc(try_buf_siz);

    *buf_siz = try_buf_siz;
    try_buf_siz /= 2;
  } while(buf == NULL && try_buf_siz >= MIN_BUF_SIZ);

  if (buf == NULL) {
    fprintf(stderr, "Out of memory.\n");
    exit(1);
  }

  return buf;
}

int main(int argc, char * argv[]) {
  size_t buf_siz;
  char * buf = alloc_buffer(&buf_siz);

  FILE * fd;
  size_t rd;
  size_t byi;
  size_t total_read;
  char last[16];

  for (int fi = 1; fi < argc; ++fi) {
    if (argc > 2) {
      printf("%s\n", argv[fi]);
    }

    fd = fopen(argv[fi], "rb");
    if (fd == NULL) {
      printf("File not found.\n");

      if (argc > 2 && fi < argc - 1) {
        printf("\n");
      }
      continue;
    }

    byi = 0;
    total_read = 0;

    while ((rd = fread(buf, 1, buf_siz, fd)) > 0) {
      total_read += rd;

      for (; byi < total_read; ++byi) {
        if (byi == 0) {
          printf("%08lx  %02x", byi, buf[byi]);
        } else if ((byi % 16) == 0) {
          printf("  |");
          for (char j = 0; j < 16; ++j) {
            printf("%c", safe_char(last[j]));
          }
          printf("|\n%08lx  %02x", byi, buf[byi]);
        } else if ((byi % 8) == 0) {
          printf("  %02x", buf[byi]);
        } else {
          printf(" %02x", buf[byi]);
        }

        last[byi % 16] = buf[byi];
      }
    }

    fclose(fd);

    if (total_read == 0) {
      printf("Empty file.\n");

      if (argc > 2 && fi < argc - 1) {
        printf("\n");
      }
      continue;
    }

    char cols_filled = (total_read % 16) == 0 ? 16 : total_read % 16;

    for (char j = 0; j < 16 - cols_filled; ++j) {
      printf("   ");
    }
    if (cols_filled < 9) {
      printf(" ");
    }

    printf("  |");
    for (char j = 0; j < cols_filled; ++j) {
      printf("%c", safe_char(last[j]));
    }
    printf("|\n%08lx\n", total_read);

    if (argc > 2 && fi < argc - 1) {
      printf("\n");
    }
  }

  return 0;
}
