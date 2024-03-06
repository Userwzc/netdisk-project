#include <func.h>

int main()
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child process ,mypid=%d,ppid=%d\n",getpid(),getppid());
    }
    else{
        //父进程fork的返回值是子进程的pid
        printf("I am parent process ,child pid=%d,,pid=%d\n",pid,getpid());
    }
    printf("you can see me twice\n");
    return 0;
}