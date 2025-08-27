CC = gcc
CFLAGS = -std=c99 -Wall -Werror -Wvla -pedantic -g -lm

SRCS = cobra.c main.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean

all: cobra

cobra: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f cobra $(OBJS)
