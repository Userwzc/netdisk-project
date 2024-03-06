CC:=gcc
CFLAGS:=-g
SRCS:=$(wildcard *.c)
BINS:=$(SRCS:%.c=%)
all:$(BINS)
%:%.c
	$(CC) -g $< -o $@ -lpthread
rebuild:clean all
clean:
	rm -rf $(BINS)
