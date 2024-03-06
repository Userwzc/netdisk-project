#include <func.h>

void sigfunc(int signum,siginfo_t *p,void *p1)
{
    printf("%d is comming\n",signum);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));//清空结构体
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO;//SA_SIGINFO 表示选择sa_sigaction而不是sa_handler作为回调函数
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}