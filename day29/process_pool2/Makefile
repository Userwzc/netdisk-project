CC:=gcc
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
CFLAGS:=-g
ELF:=process_pool
$(ELF):$(OBJS)
	$(CC) $^ -o $@
rebuild:clean $(ELF)
clean:
	rm -rf $(OBJS) $(ELF)
