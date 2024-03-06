#include <func.h>

int main()
{
    int i=10;
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,i=%d,&i=%p\n",getpid(),i,&i);     
    }else{
        //父进程fork的返回值是子进程的pid
        i=5;
        printf("I am parent process,pid=%d,i=%d,&i=%p\n",getpid(),i,&i);
    }
    return 0;
}