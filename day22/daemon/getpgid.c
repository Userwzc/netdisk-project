#include <func.h>

//子进程结束，查看进程组
int main()
{
    pid_t pid=fork();
    if(0==pid)//子进程
    {
        printf("I am child,%d,pgid=%d\n",getpid(),getpgid(0));
        while(1);
        return 1;
    }else{
        printf("I am parent %d,pgid=%d\n",getpid(),getpgid(0));
        while(1);
        return 0;
    }
}