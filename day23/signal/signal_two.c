#include <func.h>

void sigfunc(int signum)
{
    printf("before signum =%d is coming\n",signum);
    sleep(5);
    printf("after signum =%d is coming\n",signum);
}
int main()
{
    signal(SIGINT,sigfunc);
    signal(SIGQUIT,sigfunc);
    printf("process begin\n");
    while(1);
    return 0;
}