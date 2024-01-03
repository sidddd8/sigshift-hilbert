all: main
.PHONY: all

cc=gcc
CFLAGS += -Wall -Wpedantic -Werror -O4 -finline-functions
EXTRA_CFLAGS = -lm
RM=rm -f

main: src/main.c src/sig_loading_st.c src/fft.c
	$(CC) $(CFLAGS) -o main src/main.c src/sig_loading_st.c src/fft.c $(EXTRA_CFLAGS)

clean: 
	$(RM) main
	$(CC) $(CFLAGS) -o main src/main.c src/sig_loading_st.c src/fft.c $(EXTRA_CFLAGS) 
