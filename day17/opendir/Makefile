SRCS:=$(wildcard *.c)
CC:=gcc
BINS:=$(SRCS:%.c=%)
all:$(BINS)
%:%.c
	$(CC) $< -o $@

rebuild: clean all
clean:
	rm -rf $(BINS)