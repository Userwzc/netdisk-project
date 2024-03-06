#include <func.h>
int i=10;
int main()
{
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,i=%d,&i=%p\n",getpid(),i,&i);
    }else{
        i=5;
        printf("I am parent process,pid=%d,i=%d,&i=%p\n",getpid(),i,&i);
    }
    return 0;
}