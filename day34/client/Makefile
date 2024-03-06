CC:=gcc
SRCS:=$(wildcard *.c)
OBJS:=$(SRCS:%.c=%.o)
CFLAGS:=-g 
ELF:=client
$(ELF):$(OBJS)
	$(CC) $^ -o $@ -lpthread -lmysqlclient -lcrypt
rebuild:clean $(ELF)
clean:
	rm -rf $(OBJS) $(ELF)
