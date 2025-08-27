CFLAGS = -std=c99 -Wall -Werror -Wvla -g
LDFLAGS = -lm

.PHONY: all clean

all: sequencia

sequencia: main.o sequencia.o
	gcc main.o sequencia.o -g $(LDFLAGS) -o sequencia

main.o: main.c sequencia.h
	gcc $(CFLAGS) -c main.c

sequencia.o: sequencia.c sequencia.h
	gcc $(CFLAGS) -c sequencia.c

clean:
	rm -f sequencia