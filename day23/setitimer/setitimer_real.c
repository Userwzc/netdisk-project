#include <func.h>
//信号处理函数，打印当前时间
void sigfunc(int signum){
    time_t now;
    time(&now);
    printf("%s\n",ctime(&now));
}


int main()
{
    signal(SIGALRM,sigfunc);
    struct itimerval t;
    t.it_value.tv_sec=2;//初始间隔为2秒
    t.it_value.tv_usec=0;
    t.it_interval.tv_sec=3;
    t.it_interval.tv_usec=0;
    int ret;
    //想知道当前时间怎么办
    sigfunc(0);
    ret=setitimer(ITIMER_REAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    int n;
    scanf("%d",&n);
    printf("n=%d\n",n);
    while(1);
    return 0;
}