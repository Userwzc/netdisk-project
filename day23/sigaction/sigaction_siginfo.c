#include <func.h>

void sigfunc(int signum, siginfo_t *p,void *p1)
{
    printf("%d is comming,pid=%d,uid=%d\n",signum,p->si_pid,p->si_uid);
}

int main()
{
    struct sigaction act;
    memset(&act,0,sizeof(act));//清空结构体
    act.sa_sigaction=sigfunc;
    act.sa_flags=SA_SIGINFO;
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    while(1);
    return 0;
}