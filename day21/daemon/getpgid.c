#include <func.h>

int main()
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("i am child,%d\n",getpid());
        while(1);
        return 1;
    }else{
        printf("i am parent %d,pgid=%d\n",getpid(),getpgid());
        //进程组组长
        while(1);
    }
}