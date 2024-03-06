#include <func.h>

int main()
{
    struct timeval start,end;
    gettimeofday(&start,NULL);
    pid_t pid=fork();
    if(0==pid)
    {
        printf("I am child process,mypid=%d,ppid=%d\n",getpid(),getppid());     
    }else{
        wait(NULL);
        gettimeofday(&end,NULL);
        printf("usetime=%ld\n",(end.tv_sec-start.tv_sec)*1000000+
            (end.tv_usec-start.tv_usec));
        printf("I am parent process,child pid=%d,pid=%d\n",pid,getpid());
    }
    return 0;
}