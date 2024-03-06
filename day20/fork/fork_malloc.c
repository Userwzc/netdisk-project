#include <func.h>

int main()
{
    int *p=(int*)malloc(4);
    *p=10;
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%7d,*p=%2d,p=%p\n",getpid(),*p,p);
    }else{
        *p=5;
        printf("I am parent process,pid=%7d,*p=%2d,p=%p\n",getpid(),*p,p);
    }
    return 0;
}