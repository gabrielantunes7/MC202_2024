CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic -g
LDFLAGS = -lm

SRCS = hash.c lista.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: corretor

corretor: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

clean:
	rm -f corretor $(OBJS)