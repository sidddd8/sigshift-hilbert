all: main
.PHONY: all

cc=gcc
CFLAGS += -Wall -O4 -finline-functions
EXTRA_CFLAGS =
RM=rm -f

main: src/main.c src/sig_loading.c src/sig_loading.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c src/sig_loading.c src/sig_loading.h

clean: 
	$(RM) main
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c
