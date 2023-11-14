all: main
.PHONY: all

cc=gcc
CFLAGS += -Wall -O4 -finline-functions
EXTRA_CFLAGS =
RM=rm -f

main: src/main.c
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c 

clean: 
	$(RM) main
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c
