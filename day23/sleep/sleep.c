#include <func.h>

void sigfunc(int signum)
{
    
}

int main()
{
    signal(SIGALRM,sigfunc);
    alarm(3);//3秒后会向当前进程发送SIGALRM信号
    pause();
    return 0;
}