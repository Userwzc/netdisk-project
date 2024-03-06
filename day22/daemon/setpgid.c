#include <func.h>
//子进程在被创建后，单独成立一个进程组，进程组内只有自己，所以进程组id就是当前pid
int main()
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("i am child,%d,pgid=%d\n",getpid(),getpgid(0));
        setpgid(0,0); //成立一个新的进程组，进程组内只有自己，所以进程组id就是当前pid
        printf("i am child,%d,pgid=%d\n",getpid(),getpgid(0));
        while(1);
        return 1;
    }else{
        printf("i am parent %d,pgid=%d\n",getpid(),getpgid(0));
        while(1);
        return 0;
    }
}