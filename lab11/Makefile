CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic -g
LDFLAGS = -lm

SRCS = grafo.c fila.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: piscapisca

piscapisca: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f piscapisca $(OBJS)