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
    act.sa_flags=SA_SIGINFO|SA_RESTART;//SA_RESTART 让低速系统调用可以自动重启
    int ret;
    ret=sigaction(SIGINT,&act,NULL);
    ERROR_CHECK(ret,-1,"sigaction");
    char buf[1000]={0};
    ret=read(STDIN_FILENO,buf,sizeof(buf));
    printf("read %s ret=%d\n",buf,ret);
    return 0;
}