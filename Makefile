CC = clang
override CFLAGS += -lm -g -Wno-everything

SRCS = $(shell find . -name '.ccls-cache' -type d -prune -o -type f -name '*.c' -print)
OBJS = $(patsubst %.c, %.o, $(SRCS))

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

clean:
	rm -f $(OBJS) main