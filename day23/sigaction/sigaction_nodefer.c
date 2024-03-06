#include <func.h>

void sigfunc(int signum, siginfo_t * p,void *p1)
{
    printf("before signum = %d is coming\n",signum);
    sleep(5);
    printf("after signum = %d is coming\n",signum);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));//清空结构体
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO|SA_NODEFER;
    //SA_NODEFERSA_NODEFER解除所有阻塞行为。特别地，执行信号处理流程可以处理同类信号传递，按照
    //栈的方式执行。
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}