FLAGS := -std=c99 -O2 -Wall -Wextra -Wformat=2 -pedantic-errors \
	-Wfatal-errors -Wundef -Wno-unused-result -march=native \
	-fdiagnostics-color=auto

all: hexdump

hexdump: *.c
	@$(CC) $^ $(CFLAGS) -o $@

clean:
	@$(RM) -f hexdump
