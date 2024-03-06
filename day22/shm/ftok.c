#include <func.h>
//ftok 函数是一个用于生成 System V IPC（Inter-Process Communication，进程间通信）
//标识符的函数。它通常用于创建消息队列、共享内存和信号量等进程间通信的键值。
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    key_t key=ftok(argv[1],1);
    printf("key=%d\n",key);
    return 0;
}