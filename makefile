all: main
.PHONY: all

cc=gcc
CFLAGS += -Wall -Wpedantic -O4 -finline-functions
EXTRA_CFLAGS = -lm
RM=rm -f

main: src/main.c src/sig_loading_st.c src/sig_utils.c src/SIG_CONFIG.h src/processing.c
	$(CC) $(CFLAGS) -o main src/main.c src/sig_loading_st.c src/sig_utils.c src/processing.c $(EXTRA_CFLAGS)

clean: 
	$(RM) main
	$(CC) $(CFLAGS) -o main src/main.c src/sig_loading_st.c src/sig_utils.c src/processing.c $(EXTRA_CFLAGS) 
