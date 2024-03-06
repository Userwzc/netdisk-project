CC:=gcc
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
main:$(OBJS)
	$(CC) $^ -o $@
rebuild:clean main
clean:
	rm -rf $(OBJS) main
