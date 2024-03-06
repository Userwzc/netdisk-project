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
    act.sa_flags=SA_SIGINFO;
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    int ret=sigprocmask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigprocmask")
    sleep(5);//不保护，会被打断
    printf("执行业务\n");
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");

    // ret=sigprocmask(SIG_UNBLOCK,&mask,NULL);
    // ERROR_CHECK(ret,-1,"sigprocmask")
    // pause();//解除阻塞后无法使得pause就绪
    sigset_t waitset;
    sigemptyset(&waitset);
    sigsuspend(&waitset);//使用sigsuspend会捕获临界区当中的信号
    return 0;
}