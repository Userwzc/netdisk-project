#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("before signum = %d is coming\n",signum);
    sleep(5);
    printf("after signum = %d is coming\n",signum);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));  //清空结构体
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO;
    int ret;
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask,SIGQUIT);//填入3号信号
    ret=sigaction(SIGINT,&act,NULL);//2号信号信号处理行为设定
    ERROR_CHECK(ret,-1,"sigaction");
    ret=sigaction(SIGQUIT,&act,NULL);//3号信号信号处理行为设定
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}