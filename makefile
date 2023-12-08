all: main
.PHONY: all

cc=gcc
CFLAGS += -Wall -Wpedantic -Werror -O4 -finline-functions
EXTRA_CFLAGS =
RM=rm -f

main: src/main.c src/sig_loading_st.c src/sig_loading_st.h
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c src/sig_loading_st.c src/sig_loading_st.h

clean: 
	$(RM) main
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -o main src/main.c src/sig_loading_st.c src/sig_loading_st.h
