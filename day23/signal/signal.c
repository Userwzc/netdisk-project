#include <func.h>
//自定义的信号处理函数
void sigfunc(int sig_num)
{
    printf("sig_num=%d is coming\n",sig_num);
}
int main()
{
    signal(SIGINT,sigfunc);//信号处理行为设定
    printf("process begin\n");
    while(1);
    return 0;
}