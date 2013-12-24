PROG = main

CC = gcc
CFLAGS = -Os -Wextra \
	$(SOURCE_FLAGS) -g \
	-std=gnu99

OBJS = mybtree.o \
	main.o

LDFLAGS = -lm

.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -c $*.c

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(CFLAGS) $(LDFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)
