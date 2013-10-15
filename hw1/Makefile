PROG = main

CC = gcc
CFLAGS = -Os -Wextra \
	$(SOURCE_FLAGS) -g \
	-std=gnu99

OBJS = mystack.o \
	main.o

.c.o:
	$(CC) $(CFLAGS) -c $*.c

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(CFLAGS) $(OBJS)

clean:
	rm -f $(PROG) $(OBJS)
