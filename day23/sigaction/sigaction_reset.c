#include <func.h>

void sigfunc(int signum, siginfo_t * p,void *p1)
{
    printf("%d is coming\n",signum);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));//清空结构体
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO|SA_RESETHAND;
    //SA_RESETHAND 处理完捕获的信号以后，信号处理回归到默认，使用情况较少
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}