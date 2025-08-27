CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: batcomputador

batcomputador: main.o batcomputador.o
	gcc main.o batcomputador.o -g $(LDFLAGS) -o batcomputador

main.o: main.c batcomputador.h
	gcc $(CFLAGS) -c main.c

batcomputador.o: batcomputador.c batcomputador.h
	gcc $(CFLAGS) -c batcomputador.c

clean:
	rm -f batcomputador