#include <func.h>

int main()
{
    //子进程在被创建后单独成立一个进程组，和父亲不在一个进程组，父亲依然可以回收子进程
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child,%d,pgid=%d\n",getpid(),getpgid(0));
        setpgid(0,0);
        //int setpgid(pid_t pid, pid_t pgid);//将pid进程的进程组ID设置为pgid
        //如果pid为0，使用调用者的进程ID
        //如果pgid为0，则进程组ID和pid一致
        printf("I am child,%d,pgid=%d\n",getpid(),getpgid(0));
        return 1;
    }else{
        printf("I am parent,%d,pgid=%d\n",getpid(),getpgid(0));
        wait(NULL);
        while(1);
        return 0;
    }
}