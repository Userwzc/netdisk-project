#include <func.h>

int main()
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask,SIGINT);
    int ret=sigpromask(SIG_BLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigpromask");
    sleep(5); //不保护，会被打断
    printf("执行业务\n");
    sigset_t pending_set;
    sigpending(&pending_set);
    if(sigismember(&pending_set,SIGINT))     //从内核中把进程的pending信号集合取出来
    {
        printf("SIGINT is pending\n");
    }else{
        printf("SIGINT is not pending\n");
    }
    ret=sigpromask(SIG_UNBLOCK,&mask,NULL);
    ERROR_CHECK(ret,-1,"sigpromask");
    return 0;
}