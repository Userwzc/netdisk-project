CC:=gcc
CFLAGS:=-g
SRCS:=$(wildcard *.c)
BINS:=$(SRCS:%.c=%)
all:$(BINS)
%:%.c
	$(CC) $< -o $@
rebuild:clean all
clean:
	rm -rf $(BINS)