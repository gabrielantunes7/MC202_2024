CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: capicua parciais sela

capicua: capicua.c
	gcc $(CFLAGS) capicua.c -o capicua $(LDFLAGS)

parciais: parciais.c
	gcc $(CFLAGS) parciais.c -o parciais $(LDFLAGS)

sela: sela.c
	gcc $(CFLAGS) sela.c -o sela $(LDFLAGS)

clean:
	rm -f capicua parciais sela