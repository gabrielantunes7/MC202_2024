CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic -g -lm

SRCS = arvore.c pilha.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: otimizar

otimizar: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f otimizar $(OBJS)