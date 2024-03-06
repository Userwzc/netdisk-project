#include <func.h>

//父进程要查看所在的会话
int main()
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child,%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),
        getppid(),getpgid(0),getsid(0));
        while(1);
        return 1;
    }else{
        printf("I am parent,%d,ppid=%d,pgid=%d,sid=%d\n",getpid(),
        getppid(),getpgid(0),getsid(0));
        while(1);
        return 0;
    }
}