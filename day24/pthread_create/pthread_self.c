#include <func.h>

int main()
{
    //查看当前进程的pid和主线程pthread_id
    printf("pid=%d,thread id=%lu\n",getpid(),pthread_self());
    while(1);
    return 0;
}